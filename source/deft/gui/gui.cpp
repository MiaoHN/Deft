#include "gui/gui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "app/application.h"

namespace deft {

Gui::Gui() {
  init();
  initStyle();

  _logPanel   = std::make_shared<LogPanel>();
  _scenePanel = std::make_shared<ScenePanel>();
  _menuBar    = std::make_shared<MenuBar>();
}

Gui::~Gui() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Gui::init() {
  const char* glsl_version = "#version 460";

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport
                                                       // / Platform Windows
  // io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(Application::Get().getWindow().getHandler(),
                               true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void Gui::update() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  static bool               open            = true;
  static bool*              p_open          = &open;
  static bool               opt_fullscreen  = true;
  static bool               opt_padding     = false;
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window
  // not dockable into, because it would be confusing to have two docking
  // targets within each others.
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render
  // our background and handle the pass-thru hole, so we ask Begin() to not
  // render a background.
  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  // Important: note that we proceed even if Begin() returns false (aka window
  // is collapsed). This is because we want to keep our DockSpace() active. If a
  // DockSpace() is inactive, all active windows docked into it will lose their
  // parent and become undocked. We cannot preserve the docking relationship
  // between an active window and an inactive docking, otherwise any change of
  // dockspace/settings would lead to windows being stuck in limbo and never
  // being visible.
  if (!opt_padding)
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace Demo", p_open, window_flags);
  if (!opt_padding) ImGui::PopStyleVar();

  if (opt_fullscreen) ImGui::PopStyleVar(2);

  // Submit the DockSpace
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  } else {
    // ShowDockingDisabledMessage();
  }

  // 绘制菜单栏
  _menuBar->update();

  // 绘制场景
  _scenePanel->update();

  // 绘制日志
  _logPanel->update();

  ImGui::End();

  // bool flag = true;
  // ImGui::ShowDemoWindow(&flag);
}

void Gui::draw() {
  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we
  // save/restore it to make it easier to paste this code elsewhere.
  //  For this specific demo app we could also call
  //  glfwMakeContextCurrent(window) directly)
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void Gui::initStyle() {
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  // 样式详情见
  // https://github.com/ocornut/imgui/issues/707#issuecomment-512669512
  ImGuiStyle& style = ImGui::GetStyle();
  io.Fonts->AddFontFromFileTTF("assets/font/Ruda-Bold.ttf", 15.0f);
  style.FrameRounding = 4.0f;
  style.GrabRounding  = 4.0f;

  ImVec4* colors                         = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                  = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
  colors[ImGuiCol_TextDisabled]          = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
  colors[ImGuiCol_WindowBg]              = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_ChildBg]               = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border]                = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
  colors[ImGuiCol_FrameBgActive]         = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
  colors[ImGuiCol_TitleBg]               = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
  colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg]             = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
  colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
  colors[ImGuiCol_CheckMark]             = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_SliderGrab]            = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
  colors[ImGuiCol_Button]                = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ButtonHovered]         = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  colors[ImGuiCol_Header]                = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
  colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Separator]             = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_Tab]                   = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabHovered]            = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_TabActive]             = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_TabUnfocused]          = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

}  // namespace deft
