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

  _objects.emplace_back(
      std::make_shared<Box>(math::Vector3(-1.0f, 0.0f, -1.0f)));

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      _objects.emplace_back(
          std::make_shared<Box>(math::Vector3(i * 2.0f, j * 2.0f, 1.0f),
                                math::Vector3(0.2f, 0.7f, 0.7f)));
    }
  }
  _objects.emplace_back(std::make_shared<Box>(math::Vector3(2.0f, 0.0f, 1.0f),
                                              math::Vector3(0.2f, 0.7f, 0.7f)));
  _objects.emplace_back(std::make_shared<Box>(math::Vector3(3.0f, 0.0f, 3.0f),
                                              math::Vector3(0.2f, 0.7f, 0.3f)));

  _objects.emplace_back(std::make_shared<Box>(math::Vector3(5.0f, 5.0f, 5.0f),
                                              math::Vector3(1.0f, 1.0f, 1.0f)));
  _objects[28]->setLight(true);

  _objects.emplace_back(std::make_shared<SceneObject>(
      Model::Create(
          Mesh::Create(
              {
                  -5.0f, -0.5f, 5.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // 上
                  5.0f,  -0.5f, 5.0f,  0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 上
                  5.0f,  -0.5f, -5.0f, 0.0f, 1.0f, 0.0f, 2.0f, 2.0f,  // 上
                  -5.0f, -0.5f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,  // 上
              },
              {
                  {"aPos", ElementType::Float3},
                  {"aNormal", ElementType::Float3},
                  {"aTexCoord", ElementType::Float2},
              },
              {
                  0, 1, 2, 0, 2, 3,  //
              }),
          Texture::Create("assets/texture/metal.png")),
      Transform(math::Vector3(0.0f, 0.0f, 0.0f))));

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
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

  for (auto& object : _objects) {
    if (object->isLight()) {
      render.addLight(object->getEntityId());
    }
  }
  for (auto& object : _objects) {
    render.submit(object, _shader, object->getTransform().position);
  }

  _frameBuffer->unBind();
}

std::shared_ptr<FrameBuffer>& Scene::getFrameBuffer() { return _frameBuffer; }

}  // namespace deft
