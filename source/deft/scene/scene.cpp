#include "scene/scene.h"

#include <glad/glad.h>

#include "pch.h"

namespace deft {

Scene::Scene() {
  for (int i = 0; i < 2; ++i) {
    _models.emplace_back(Model::Create(
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
        }));
  };

  _models.emplace_back(Model::Create(
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
      }));

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
                                     "assets/shader/default.frag");

  _texture = std::make_shared<Texture>("assets/texture/container.jpg");

  _floorTexture = std::make_shared<Texture>("assets/texture/metal.png");
}

Scene::~Scene() {}

void Scene::tick(float dt) {}

void Scene::render(Renderer& render) {
  render.submit(_models[0], _shader, _texture, {-1.0f, 0.0f, -1.0f});
  render.submit(_models[1], _shader, _texture, {2.0f, 0.0f, 0.0f});
  render.submit(_models[2], _shader, _floorTexture, {0.0f, 0.0f, 0.0f});
}

}  // namespace deft
