#include "scene/scene.h"

#include <glad/glad.h>

#include "app/application.h"
#include "pch.h"
#include "scene/box.h"

namespace deft {

Scene::Scene() {
  _frameBuffer =
      FrameBuffer::Create({Application::Get().getWindow().getWidth(),
                           Application::Get().getWindow().getHeight()});

  _boxObjects.emplace_back(
      std::make_shared<Box>(math::Vector3(-1.0f, 0.0f, -1.0f)));

  _boxObjects.emplace_back(std::make_shared<Box>(
      math::Vector3(2.0f, 2.0f, 1.0f), math::Vector3(0.2f, 0.7f, 0.7f)));

  _boxObjects.emplace_back(std::make_shared<Box>(
      math::Vector3(2.0f, 0.0f, 1.0f), math::Vector3(0.2f, 0.7f, 0.7f)));
  _boxObjects.emplace_back(std::make_shared<Box>(
      math::Vector3(3.0f, 0.0f, 3.0f), math::Vector3(0.2f, 0.7f, 0.3f)));

  auto lightBox = std::make_shared<Box>(math::Vector3(5.0f, 5.0f, 5.0f),
                                        math::Vector3(1.0f, 1.0f, 1.0f), true);

  _lightObjects.emplace_back(lightBox);

  _lightShader = std::make_shared<Shader>("assets/shader/light.vert",
                                          "assets/shader/light.frag");

  _boxShader = std::make_shared<Shader>("assets/shader/default.vert",
                                        "assets/shader/default.frag");
}

Scene::~Scene() {}

void Scene::tick(float dt) {}

void Scene::render(Renderer& render) {
  _frameBuffer->bind();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto& lightObject : _lightObjects) {
    render.addLight(lightObject->getEntityId());
  }

  for (auto& lightObject : _lightObjects) {
    render.submit(lightObject, _lightShader,
                  lightObject->getTransform().position);
  }

  for (auto& boxObject : _boxObjects) {
    render.submit(boxObject, _boxShader, boxObject->getTransform().position);
  }

  _frameBuffer->unBind();
}

std::shared_ptr<FrameBuffer>& Scene::getFrameBuffer() { return _frameBuffer; }

}  // namespace deft
