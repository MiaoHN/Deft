#include "scene/scene.h"

#include <glad/glad.h>

#include "pch.h"
#include "util/obj_loader.h"

namespace deft {

Scene::Scene() {
  _model = ObjLoader::Load("assets/model/standford-bunny.obj");

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
                                     "assets/shader/default.frag");

  _shader->setInt("diffuseTexture", 0);

  _texture = std::make_shared<Texture>("assets/texture/wall.jpg");
}

Scene::~Scene() {}

void Scene::tick(float dt) {}

void Scene::render(Renderer& render) {
  render.submit(_model, _shader, _texture, {0.0f, 0.0f, -2.0f});
}

}  // namespace deft
