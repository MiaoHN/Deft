add_subdirectory(glfw)

set(VENDOR_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/stb/include
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui_zmo
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
  PARENT_SCOPE
)

file(
  GLOB
  IMGUI_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp"
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

file(
  GLOB
  IMGUIZMO_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui_zmo/*.cpp"
)

set(VENDOR_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/stb/src/stb_image.cpp
  ${IMGUI_SOURCES}
  ${IMGUIZMO_SOURCES}
  PARENT_SCOPE
)

set(VENDOR_LIBRARY
  glfw
  PARENT_SCOPE
)