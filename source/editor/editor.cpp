#include "editor.h"

namespace deft {

void Editor::initialize() {
  RenderAPI::Set(RenderAPI::OpenGL);

  _scene                  = std::make_shared<Scene>();
  _gui                    = std::make_unique<Gui>(&_scene->getRegistry());
  _editorCameraController = std::make_shared<CameraController>();

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
}

void Editor::tick(float dt) {
  if (_gui->isScenePanelHovered()) {
    if (Input::IsMouseButtonPress(MouseButton::Right)) {
      _editorCameraController->setEnable(true);
    } else {
      _editorCameraController->setEnable(false);
    }
  } else {
    _editorCameraController->setEnable(false);
  }

  _editorCameraController->tick(dt);
  _gui->update(_frameBuffer);

  _frameBuffer->bind();

  RenderCommand::ClearColor(math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));
  RenderCommand::Clear();

  _scene->updateEditMode(dt, _editorCameraController->getCamera());

  _frameBuffer->unBind();

  _gui->draw();
}

Application* CreateApplication() { return new Editor; }

}  // namespace deft
