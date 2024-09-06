cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENGINE_PYTHON_BINDINGS "" ON)
option(ENGINE_STATIC "" ON)
option(USE_SDL_SUBMODULE "Use SDL from git in submodules" ON)

include_directories(include)
include_directories(submodules/shadercross)

add_compile_options(-fno-stack-protector -fno-fast-math  -fPIC)

if(EMSCRIPTEN)
  set(ENGINE_STATIC ON)
endif()

if(ENGINE_STATIC)
  set(SDL_STATIC ON)
  set(SDL_SHARED OFF)
  add_library(${SKBUILD_PROJECT_NAME} STATIC)
else()
  set(SDL_STATIC OFF)
  set(SDL_SHARED ON)
  add_library(${SKBUILD_PROJECT_NAME} SHARED)
endif()

if(USE_SDL_SUBMODULE)
    add_subdirectory(submodules/sdl)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
endif()

target_sources(${SKBUILD_PROJECT_NAME}
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/graphics/window.ixx
      src/main.ixx

      src/math/math.ixx
      src/math/utils.ixx

      src/math/coordinates.ixx
      src/math/vectors.ixx

      src/math/matrices/matrix.ixx
)

target_compile_options(${SKBUILD_PROJECT_NAME} PRIVATE -Wall)
target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE SDL3::SDL3)

if(EMSCRIPTEN)
  add_link_options(-fexceptions)
endif()

if(ENGINE_PYTHON_BINDINGS)
  set(PY_MODULE ${SKBUILD_PROJECT_NAME}_py)
  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

  # execute_process(
  #   COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  #   OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
  # find_package(nanobind CONFIG REQUIRED)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/nanobind)
  message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  message(STATUS "Python_VERSION: ${Python_VERSION}")

  nanobind_add_module(${PY_MODULE} NB_STATIC python_module/main_python.cpp)

  target_compile_options(${PY_MODULE} PRIVATE -Wall)

  target_link_libraries(${PY_MODULE} PRIVATE ${SKBUILD_PROJECT_NAME})

  add_dependencies(${PY_MODULE} ${SKBUILD_PROJECT_NAME})

  install(TARGETS ${PY_MODULE} DESTINATION .)
endif()

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  if(NOT MSVC)
      add_compile_options(-Wfatal-errors)
  endif()
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
    add_compile_options(-O3)
    if(MSVC)
      add_compile_options(-WX)
  else()
      add_compile_options(-Werror)
  endif()
endif()
