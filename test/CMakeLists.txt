set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/test/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/test/release)

include_directories(${SOURCE_ROOT})

add_executable(math_test math_test.cpp)
add_executable(obj_test obj_test.cpp)