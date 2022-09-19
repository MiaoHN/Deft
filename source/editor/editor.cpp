#include "editor.h"

#include <GLFW/glfw3.h>
#include <ImGuizmo.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

namespace deft {

void Editor::initialize() {
  RenderAPI::Set(RenderAPI::OpenGL);

  _scene        = std::make_shared<Scene>();
  _editorCamera = std::make_shared<EditorCamera>();

  _frameBuffer = FrameBuffer::Create(FrameBufferData(1600.0f, 900.0f));

  ShaderLib::Add("default", Shader::Create("assets/shader/default.vert",
                                           "assets/shader/default.frag"));
  UniformBufferLib::Add("cameraUniform",
                        UniformBuffer::Create(sizeof(CameraData), 0));

  auto& _registry = _scene->getRegistry();

  Entity box1 = _registry.createEntity("Box1");
  Entity box2 = _registry.createEntity("Box2");

  TransformComponent transform;
  transform.position = {0.0f, 0.0f, 0.0f};
  transform.scale    = {1.0f, 1.0f, 1.0f};
  transform.rotation = {0.0f, 0.0f, 0.0f};
  box1.addComponent(transform);
  transform.position = {2.0f, 1.0f, -1.5f};
  transform.scale    = {1.0f, 1.0f, 1.0f};
  transform.rotation = {0.0f, 0.0f, 0.0f};
  box2.addComponent(transform);

  MeshComponent meshComponent;
  meshComponent.mesh = Mesh::Cube();

  meshComponent.mesh->addTexture(
      TextureType::Diffuse, Texture::Create("assets/texture/container.jpg"));

  auto texture1 = Texture::Create(1, 1);

  unsigned int color = 0xffffffff;
  texture1->setData(&color, sizeof(color));
  meshComponent.mesh->addTexture(TextureType::Specular, texture1);
  box1.addComponent(meshComponent);
  box2.addComponent(meshComponent);

  Entity directionLight = _registry.createEntity("Direction Light");

  LightComponent lightComponent;
  lightComponent.type      = LightType::Direction;
  lightComponent.direction = math::Vector3(-1.0f, -1.0f, -1.0f);
  lightComponent.ambient   = math::Vector3(0.05f, 0.05f, 0.05f);
  lightComponent.diffuse   = math::Vector3(0.4f, 0.4f, 0.4f);
  lightComponent.specular  = math::Vector3(0.5f, 0.5f, 0.5f);

  directionLight.addComponent(lightComponent);

  Entity pointLight        = _registry.createEntity("Point Light");
  lightComponent.type      = LightType::Point;
  lightComponent.ambient   = math::Vector3(0.05f, 0.05f, 0.05f);
  lightComponent.diffuse   = math::Vector3(0.8f, 0.8f, 0.8f);
  lightComponent.specular  = math::Vector3(1.0f, 1.0f, 1.0f);
  lightComponent.constant  = 1.0f;
  lightComponent.linear    = 0.09f;
  lightComponent.quadratic = 0.032f;

  pointLight.addComponent(lightComponent);
  transform.position = math::Vector3(-2.0f, -4.0f, 3.0f);
  transform.rotation = math::Vector3(0.0f, 0.0f, 0.0f);
  transform.scale    = math::Vector3(0.2f, 0.2f, 0.2f);

  pointLight.addComponent(transform);
  MeshComponent pointLightMeshComponent;
  pointLightMeshComponent.mesh = Mesh::Cube();

  auto texture2 = Texture::Create(1, 1);
  color         = 0xffffffff;
  texture2->setData(&color, sizeof(color));
  pointLightMeshComponent.mesh->addTexture(TextureType::Diffuse, texture2);
  pointLight.addComponent(pointLightMeshComponent);

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

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // 样式详情见
  // https://github.com/ocornut/imgui/issues/707#issuecomment-512669512
  ImGuiStyle& style = ImGui::GetStyle();
  io.Fonts->AddFontFromFileTTF("assets/font/Ruda-Bold.ttf", 20.0f);
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

  _logPanel = std::make_shared<LogPanel>();
}

void Editor::tick(float dt) {
  if (_isHovered) {
    if (Input::IsMouseButtonPress(MouseButton::Right)) {
      _editorCamera->setEnable(true);
    } else {
      _editorCamera->setEnable(false);
    }
  } else {
    _editorCamera->setEnable(false);
  }

  _editorCamera->tick(dt);

  _frameBuffer->bind();

  RenderCommand::ClearColor(math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));
  RenderCommand::Clear();

  _scene->updateEditMode(dt, _editorCamera);

  _frameBuffer->unBind();

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  static bool               open            = true;
  static bool*              p_open          = &open;
  static bool               opt_fullscreen  = true;
  static bool               opt_padding     = false;
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Deft", p_open, window_flags);
  ImGui::PopStyleVar();

  ImGui::PopStyleVar(2);

  // Submit the DockSpace
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::Begin("Renderer");
  ImGui::Text("fps: %d", Application::Get().getFps());
  std::string renderAPIType = "UnKnown";
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL: {
      renderAPIType = "OpenGL";
      break;
    }
  }
  ImGui::Text("Render API: %s", renderAPIType.c_str());

  int button;
  ImGui::RadioButton("Translate", &button, 1);
  ImGui::RadioButton("Rotate", &button, 2);
  ImGui::RadioButton("Scale", &button, 3);
  if (button == 1) {
    _gizmoType = ImGuizmo::OPERATION::TRANSLATE;
  }
  if (button == 2) {
    _gizmoType = ImGuizmo::OPERATION::ROTATE;
  }
  if (button == 3) {
    _gizmoType = ImGuizmo::OPERATION::SCALE;
  }

  ImGui::End();

  _logPanel->update();

  unsigned int sceneTexture = _frameBuffer->getColorAttachment();
  ImGui::Begin("Scene");
  if (ImGui::IsWindowHovered()) {
    _isHovered = true;
  } else {
    _isHovered = false;
  }
  ImGui::Image(reinterpret_cast<void*>(sceneTexture), ImVec2{992.0f, 558.0f},
               ImVec2{0, 1}, ImVec2{1, 0});

  // ImGuizmo
  float                   viewManipulateRight = io.DisplaySize.x;
  float                   viewManipulateTop   = 0;
  static ImGuiWindowFlags gizmoWindowFlags    = 0;
  ImGuizmo::SetDrawlist();
  float windowWidth  = (float)ImGui::GetWindowWidth();
  float windowHeight = (float)ImGui::GetWindowHeight();
  ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
                    windowWidth, windowHeight);
  viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
  viewManipulateTop   = ImGui::GetWindowPos().y;
  ImGuiWindow* window = ImGui::GetCurrentWindow();
  gizmoWindowFlags    = ImGui::IsWindowHovered() &&
                             ImGui::IsMouseHoveringRect(window->InnerRect.Min,
                                                        window->InnerRect.Max)
                            ? ImGuiWindowFlags_NoMove
                            : 0;

  auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
  auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
  auto viewportOffset    = ImGui::GetWindowPos();
  _viewportBounds[0]     = {viewportMinRegion.x + viewportOffset.x,
                        viewportMinRegion.y + viewportOffset.y};
  _viewportBounds[1]     = {viewportMaxRegion.x + viewportOffset.x,
                        viewportMaxRegion.y + viewportOffset.y};

  if (_selected && _selectedEntity.haveComponent<TransformComponent>()) {
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();

    ImGuizmo::SetRect(_viewportBounds[0].x, _viewportBounds[0].y,
                      _viewportBounds[1].x - _viewportBounds[0].x,
                      _viewportBounds[1].y - _viewportBounds[0].y);

    auto        cameraView       = _editorCamera->getView();
    auto const& cameraProjection = _editorCamera->getProjection();

    math::Matrix4 identityMatrix(1.0f);
    auto&  transform = _selectedEntity.getComponent<TransformComponent>();
    float* matrix;

    math::Matrix4 transformMatrix = transform.getTransform();

    bool  snap      = Input::IsKeyPress(KeyCode::LeftControl);
    float snapValue = 0.5f;

    if (_gizmoType == ImGuizmo::OPERATION::ROTATE) {
      snapValue = 45.0f;
    }

    float snapValues[3] = {snapValue, snapValue, snapValue};

    // ImGuizmo::DrawGrid(cameraView.ptr(), cameraProjection.ptr(),
    //                    identityMatrix.ptr(), 100.f);

    ImGuizmo::Manipulate(cameraView.ptr(), cameraProjection.ptr(),
                         (ImGuizmo::OPERATION)_gizmoType, ImGuizmo::LOCAL,
                         transformMatrix.ptr(), nullptr,
                         snap ? snapValues : nullptr);
    if (ImGuizmo::IsUsing()) {
      math::Vector3 translation, rotation, scale;
      math::decomposeTransform(transformMatrix, translation, rotation, scale);

      math::Vector3 deltaRotation = rotation - transform.rotation;

      transform.position = translation;
      transform.rotation += deltaRotation;
      transform.scale = scale;
    }
  }

  ImGui::End();

  // 绘制实体列表
  ImGui::Begin("Scene Hierarchy");
  if (ImGui::Button("Add")) {
    _scene->getRegistry().createEntity();
  }

  for (auto& entity : _scene->getRegistry().getEntiesUsed()) {
    if (ImGui::Button(entity.getName().c_str())) {
      _selected       = true;
      _selectedEntity = entity;
    }
  }

  ImGui::End();

  // 绘制实体属性
  ImGui::Begin("Properties");

  if (_selected) {
    Entity entity = _selectedEntity;

    ImGui::LabelText("Entity Name", entity.getName().c_str());

    char buf[128] = "";
    if (ImGui::InputText("Rename", buf, 128)) {
      std::string newName = std::string(buf, strlen(buf));
      entity.setName(newName);
    }

    if (ImGui::Button("Add Transform")) {
      if (!entity.haveComponent<TransformComponent>()) {
        entity.addComponent(TransformComponent());
      }
    }
    if (ImGui::Button("Add Mesh(cube)")) {
      if (!entity.haveComponent<MeshComponent>()) {
        if (!entity.haveComponent<TransformComponent>()) {
          entity.addComponent(TransformComponent());
        }
        MeshComponent meshComponent;
        meshComponent.mesh = Mesh::Cube();
        meshComponent.mesh->addTexture(
            TextureType::Diffuse,
            Texture::Create("assets/texture/container.jpg"));
        unsigned int color   = 0xffffffff;
        auto         texture = Texture::Create(1, 1);
        texture->setData(&color, sizeof(color));
        meshComponent.mesh->addTexture(TextureType::Specular, texture);
        entity.addComponent(meshComponent);
      }
    }

    // 显示位置信息
    if (_scene->getRegistry().haveComponent<TransformComponent>(entity)) {
      auto& transform =
          _scene->getRegistry().getComponent<TransformComponent>(entity);
      if (ImGui::TreeNode("Transform")) {
        ImGui::DragFloat3("Position", &transform.position.x);
        ImGui::DragFloat3("Rotation", &transform.rotation.x);
        ImGui::DragFloat3("Scale", &transform.scale.x);
        ImGui::TreePop();
      }
    }

    // 显示材质信息
    if (_scene->getRegistry().haveComponent<MeshComponent>(entity)) {
      auto& meshComponent =
          _scene->getRegistry().getComponent<MeshComponent>(entity);
      if (ImGui::TreeNode("Mesh")) {
        auto& textures = meshComponent.mesh->getTextures();
        if (textures.find(TextureType::Diffuse) != textures.end()) {
          unsigned int textureId = textures[TextureType::Diffuse]->getId();
          ImGui::Text("Diffuse");
          ImGui::Image(reinterpret_cast<void*>(textureId), ImVec2{80.0f, 80.0f},
                       ImVec2{0, 1}, ImVec2{1, 0});
          ImGui::Separator();
        }
        if (textures.find(TextureType::Specular) != textures.end()) {
          unsigned int textureId = textures[TextureType::Specular]->getId();
          ImGui::Text("Specular");
          ImGui::Image(reinterpret_cast<void*>(textureId), ImVec2{80.0f, 80.0f},
                       ImVec2{0, 1}, ImVec2{1, 0});
          ImGui::Separator();
        }
        ImGui::TreePop();
      }
    }

    // 显示光照信息
    if (_scene->getRegistry().haveComponent<LightComponent>(entity)) {
      if (ImGui::TreeNode("Light")) {
        auto& lightComponent = entity.getComponent<LightComponent>();
        switch (lightComponent.type) {
          case LightType::Direction: {
            ImGui::DragFloat3("direction", &lightComponent.direction.x);
            break;
          }
          case LightType::Point: {
            ImGui::DragFloat("constant", &lightComponent.constant, 0.05, 0, 1);
            ImGui::DragFloat("linear", &lightComponent.linear, 0.05, 0, 1);
            ImGui::DragFloat("quadratic", &lightComponent.quadratic, 0.05, 0,
                             1);
            break;
          }
          case LightType::Spot: {
            ImGui::DragFloat3("direction", &lightComponent.direction.x);
            ImGui::DragFloat("cutOff", &lightComponent.cutOff);
            ImGui::DragFloat("outerCutOff", &lightComponent.outerCutOff);
            ImGui::DragFloat("constant", &lightComponent.constant, 0.05, 0, 1);
            ImGui::DragFloat("linear", &lightComponent.linear, 0.05, 0, 1);
            ImGui::DragFloat("quadratic", &lightComponent.quadratic, 0.05, 0,
                             1);
            break;
          }
        }
        ImGui::DragFloat3("ambient", &lightComponent.ambient.x, 0.05, 0, 1);
        ImGui::DragFloat3("diffuse", &lightComponent.diffuse.x, 0.05, 0, 1);
        ImGui::DragFloat3("specular", &lightComponent.specular.x, 0.05, 0, 1);

        ImGui::TreePop();
      }
    }
  }
  ImGui::End();

  ImGui::End();

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

Application* CreateApplication() { return new Editor; }

}  // namespace deft
