set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release/test)

include_directories(${SOURCE_ROOT})

add_executable(math_test math_test.cpp)
target_link_libraries(math_test PRIVATE ${PROJECT_NAME})
add_executable(obj_test obj_test.cpp)
target_link_libraries(obj_test PRIVATE ${PROJECT_NAME})

add_custom_command(
  TARGET obj_test
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:obj_test>/assets
)