add_subdirectory(glfw)

set(VENDOR_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/stb/include
  PARENT_SCOPE
)

set(VENDOR_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/stb/src/stb_image.cpp
  PARENT_SCOPE
)

set(VENDOR_LIBRARY
  glfw
  PARENT_SCOPE
)