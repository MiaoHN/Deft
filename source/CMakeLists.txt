set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/deft/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/deft/release)

add_subdirectory(deft)

# file(GLOB_RECURSE DEFT_SOURCE
# ${SOURCE_ROOT}/*.cpp
# )

# add_executable(
# ${PROJECT_NAME}
# ${DEFT_SOURCE}
# ${VENDOR_SOURCE}
# )

# target_include_directories(
# ${PROJECT_NAME}
# PUBLIC
# ${SOURCE_ROOT}
# ${VENDOR_INCLUDE}
# )

# target_link_libraries(
# ${PROJECT_NAME}
# PUBLIC
# ${VENDOR_LIBRARY}
# )

# target_precompile_headers(
# ${PROJECT_NAME}
# PUBLIC
# ${SOURCE_ROOT}/pch.h
# )
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
