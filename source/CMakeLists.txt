set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/deft/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/deft/release)

add_subdirectory(deft)

add_executable(editor main.cpp)
target_link_libraries(editor PUBLIC ${PROJECT_NAME})
target_include_directories(editor PUBLIC ${SOURCE_ROOT})

add_custom_command(
  TARGET editor
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:editor>/assets
)

add_custom_command(
  TARGET editor
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${PROJECT_SOURCE_DIR}/assets/layout/imgui.ini
  $<TARGET_FILE_DIR:editor>/imgui.ini
)
