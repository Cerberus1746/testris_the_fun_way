cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_compile_options(-fno-stack-protector)

option(PYTHON_BINDINGS "Install the Python bindings" ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fmodules-ts)
endif()

if(EMSCRIPTEN)
  add_compile_options(${TARGET_NAME} -fexceptions)
  add_link_options(${TARGET_NAME} -fexceptions)
endif()

include_directories(include)

add_library(${SKBUILD_PROJECT_NAME} STATIC)
target_sources(${SKBUILD_PROJECT_NAME}
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/math/math.cpp
      src/math/utils.cpp

      src/math/vectors.cpp

      src/math/matrices/matrix.cpp
)

if(PYTHON_BINDINGS)
  set(PY_MODULE_LIBARY_NAME ${SKBUILD_PROJECT_NAME}Py)
  find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

  #execute_process(
  #  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  #  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
  #find_package(nanobind CONFIG REQUIRED)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/nanobind)
  message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  message(STATUS "Python_VERSION: ${Python_VERSION}")

  nanobind_add_module(${PY_MODULE_LIBARY_NAME} python_module/module.cpp)

  target_link_libraries(${PY_MODULE_LIBARY_NAME} PUBLIC ${SKBUILD_PROJECT_NAME})

  install(TARGETS ${PY_MODULE_LIBARY_NAME} DESTINATION .)
endif()
