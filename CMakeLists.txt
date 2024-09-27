cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ON)

option(ENGINE_PYTHON_BINDINGS "Create the python bindings" ON)
option(ENGINE_STATIC "Build SDL and the engine statically" ON)
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

add_subdirectory(submodules/tomlplusplus)

if(USE_SDL_SUBMODULE)
    add_subdirectory(submodules/sdl)
else()
  if(ENGINE_STATIC)
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-static)
  else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-dynamic)
  endif()
endif()

target_sources(${SKBUILD_PROJECT_NAME}
  PUBLIC
    FILE_SET all_modules TYPE CXX_MODULES FILES
      src/utils.ixx
      src/main.ixx
      src/math/utils.ixx
      src/math/matrix.ixx
      src/math/math.ixx

      src/math/coordinates/cartesian.ixx
      src/math/coordinates/vectors.ixx
      src/math/coordinates/points.ixx

      src/graphics/mesh.ixx
      src/graphics/window.ixx

      src/math/geometry/geometry.ixx
      src/math/geometry/basic_shapes.ixx



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

  nanobind_add_module(${PY_MODULE} NB_STATIC src/python_module/main.cpp)

  target_sources(${PY_MODULE}
    PUBLIC
      FILE_SET all_modules TYPE CXX_MODULES FILES
        src/python_module/vectors.ixx
  )

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
