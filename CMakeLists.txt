cmake_minimum_required(VERSION 3.24)

project(Deft VERSION 0.0.1)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/source)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

add_subdirectory(vendor)
add_subdirectory(source)
add_subdirectory(test)