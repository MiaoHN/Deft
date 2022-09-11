#include "scene/scene.h"

#include <glad/glad.h>

#include "app/application.h"
#include "pch.h"

namespace deft {

Scene::Scene() {
  _frameBuffer =
      FrameBuffer::Create({Application::Get().getWindow().getWidth(),
                           Application::Get().getWindow().getHeight()});

  _objects.emplace_back(std::make_shared<SceneObject>(
      Model::Create(
          Mesh::Create(
              {
                  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 前
                  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 前
                  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 前
                  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 前

                  0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  // 后
                  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,  // 后
                  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  // 后
                  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,  // 后

                  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // 左
                  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // 左
                  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,  // 左
                  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // 左

                  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 右
                  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 右
                  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 右
                  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 右

                  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // 上
                  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 上
                  0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // 上
                  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 上

                  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  // 下
                  0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  // 下
                  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,  // 下
                  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  // 下
              },
              {
                  {"aPos", ElementType::Float3},
                  {"aNormal", ElementType::Float3},
                  {"aTexCoord", ElementType::Float2},
              },
              {
                  0,  1,  2,  0,  2,  3,   //
                  4,  5,  6,  4,  6,  7,   //
                  8,  9,  10, 8,  10, 11,  //
                  12, 13, 14, 12, 14, 15,  //
                  16, 17, 18, 16, 18, 19,  //
                  20, 21, 22, 20, 22, 23,  //

              }),
          Texture::Create("assets/texture/container.jpg")),
      Transform(math::Vector3(-1.0f, 0.0f, -1.0f))));

  _objects.emplace_back(std::make_shared<SceneObject>(
      Model::Create(
          Mesh::Create(
              {
                  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 前
                  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 前
                  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 前
                  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 前

                  0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  // 后
                  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,  // 后
                  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  // 后
                  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,  // 后

                  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // 左
                  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // 左
                  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,  // 左
                  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // 左

                  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 右
                  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 右
                  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 右
                  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 右

                  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // 上
                  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 上
                  0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // 上
                  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 上

                  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  // 下
                  0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  // 下
                  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,  // 下
                  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  // 下
              },
              {
                  {"aPos", ElementType::Float3},
                  {"aNormal", ElementType::Float3},
                  {"aTexCoord", ElementType::Float2},
              },
              {
                  0,  1,  2,  0,  2,  3,   //
                  4,  5,  6,  4,  6,  7,   //
                  8,  9,  10, 8,  10, 11,  //
                  12, 13, 14, 12, 14, 15,  //
                  16, 17, 18, 16, 18, 19,  //
                  20, 21, 22, 20, 22, 23,  //

              }),
          Texture::Create("assets/texture/container.jpg")),
      Transform(math::Vector3(2.0f, 0.0f, 1.0f))));

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
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto& object : _objects) {
    render.submit(object->getModel(), _shader, object->getTransform().position);
  }

  _frameBuffer->unBind();
}

std::shared_ptr<FrameBuffer>& Scene::getFrameBuffer() { return _frameBuffer; }

}  // namespace deft
