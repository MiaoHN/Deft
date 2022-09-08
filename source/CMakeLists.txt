file(GLOB_RECURSE DEFT_SOURCE
  ${SOURCE_ROOT}/*.cpp
)

add_executable(${PROJECT_NAME} ${DEFT_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_ROOT})
