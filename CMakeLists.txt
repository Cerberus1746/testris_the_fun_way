cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wfatal-errors)

set(PYTHON_BINDINGS ON)
option(USE_SDL_SUBMODULE "Use SDL from git in submodules" ON)

if(USE_SDL_SUBMODULE)
    add_subdirectory(submodules/sdl)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

include_directories(include)
include_directories(submodules/shadercross)

if(EMSCRIPTEN)
  add_library(${SKBUILD_PROJECT_NAME} STATIC)
else()
  add_library(${SKBUILD_PROJECT_NAME} SHARED)
endif()

target_sources(${SKBUILD_PROJECT_NAME}
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/graphics/window.ixx
      src/fun_engine.ixx

      src/math/math.ixx
      src/math/utils.ixx

      src/math/vectors.ixx

      src/math/matrices/matrix.ixx
)

target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE SDL3::SDL3)

if(EMSCRIPTEN)
  add_link_options(-fexceptions)
endif()

if(PYTHON_BINDINGS)
  set(PY_MODULE ${SKBUILD_PROJECT_NAME}Py)
  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

  # execute_process(
  #   COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  #   OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
  # find_package(nanobind CONFIG REQUIRED)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/nanobind)
  message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  message(STATUS "Python_VERSION: ${Python_VERSION}")

  nanobind_add_module(${PY_MODULE} python_module/main_python.cpp)

  target_link_libraries(${PY_MODULE} PRIVATE ${SKBUILD_PROJECT_NAME})

  target_compile_options(${PY_MODULE} PUBLIC
    -fmodules
    -fbuiltin-module-map
    -fimplicit-module-maps
    -fmodules-cache-path=${CMAKE_BINARY_DIR}/clang-modules-cache
  )

  add_dependencies(${PY_MODULE} ${SKBUILD_PROJECT_NAME})

  install(TARGETS ${PY_MODULE} DESTINATION .)
endif()
