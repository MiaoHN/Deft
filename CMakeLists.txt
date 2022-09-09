cmake_minimum_required(VERSION 3.24)

project(Deft VERSION 0.0.1)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/source)

add_subdirectory(vendor)
add_subdirectory(source)
add_subdirectory(test)