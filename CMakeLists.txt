cmake_minimum_required(VERSION 3.28)
project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/nanobind)

message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
message(STATUS "Python_VERSION: ${Python_VERSION}")

nanobind_add_module(${SKBUILD_PROJECT_NAME}
  python_module/main_python.cpp)

target_sources(${SKBUILD_PROJECT_NAME}
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/funengine.cpp
      src/graphics/graphics.cpp

      src/math/math.cpp
      src/math/utils.cpp

      src/math/vectors.cpp

      src/math/matrices/matrix.cpp
)

target_compile_options(${SKBUILD_PROJECT_NAME} PRIVATE -fmodules)
target_link_options(${SKBUILD_PROJECT_NAME} PRIVATE -fmodules)

if(EMSCRIPTEN)
  add_link_options(-fexceptions)
  target_link_options(${SKBUILD_PROJECT_NAME} PRIVATE
    -sUSE_GLFW=3
    -sUSE_WEBGPU
    -sASYNCIFY)
else()
  add_subdirectory(submodules/WebGPU-distribution)
endif()
target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE webgpu)

install(TARGETS ${SKBUILD_PROJECT_NAME} DESTINATION .)
