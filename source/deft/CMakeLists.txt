file(GLOB_RECURSE DEFT_SOURCE
  ${SOURCE_ROOT}/*.cpp
)

add_library(
  ${PROJECT_NAME}
  STATIC
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