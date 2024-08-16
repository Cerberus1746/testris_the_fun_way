cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(PYTHON_INSTALL  "Install the Python bindings" ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fmodules-ts)
endif()

include_directories(include)

add_library(funengine STATIC)
target_sources(funengine
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/math/math.cpp
      src/math/utils.cpp

      src/math/vectors/vector.cpp
      src/math/vectors/vector2.cpp
      src/math/vectors/vector3.cpp
      src/math/vectors/vector4.cpp

      src/math/matrices/matrix.cpp
)


if(PYTHON_INSTALL)
  add_subdirectory(submodules/nanobind)

  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
  message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  message(STATUS "Python_VERSION: ${Python_VERSION}")

  find_package(nanobind CONFIG REQUIRED)

  nanobind_add_module(funenginepy python_module/module.cpp)
  target_link_libraries(funenginepy PUBLIC funengine)

  install(TARGETS funenginepy DESTINATION .)
endif()
