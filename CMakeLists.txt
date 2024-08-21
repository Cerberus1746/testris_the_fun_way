cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(PYTHON_BINDINGS  "Install the Python bindings" ON)

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

if(PYTHON_BINDINGS)
  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

  execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
  #find_package(nanobind CONFIG REQUIRED)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/nanobind)
  message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  message(STATUS "Python_VERSION: ${Python_VERSION}")

  nanobind_add_module(funenginepy python_module/module.cpp)

  target_link_libraries(funenginepy PUBLIC funengine)

  install(TARGETS funenginepy DESTINATION .)
endif()
