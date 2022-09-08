file(GLOB_RECURSE DEFT_SOURCE
  ${SOURCE_ROOT}/*.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${DEFT_SOURCE}
  ${VENDOR_SOURCE}
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${SOURCE_ROOT}
  ${VENDOR_INCLUDE}
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  ${VENDOR_LIBRARY}
)

target_precompile_headers(
  ${PROJECT_NAME}
  PUBLIC
  ${SOURCE_ROOT}/pch.h
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
