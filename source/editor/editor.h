#ifndef __DEFT_EDITOR_H__
#define __DEFT_EDITOR_H__

#include "deft.h"
#include "gui/gui.h"

namespace deft {

class EditorLayer : public Layer {
 public:
  EditorLayer() {
    _scene                  = std::make_shared<Scene>();
    _gui                    = std::make_unique<Gui>(&_scene->getRegistry());
    _editorCameraController = std::make_shared<CameraController>();

    _frameBuffer = FrameBuffer::Create(FrameBufferData(1600.0f, 900.0f));

    ShaderLib::Add("default",
                   std::make_shared<Shader>("assets/shader/default.vert",
                                            "assets/shader/default.frag"));
    UniformBufferLib::Add("cameraUniform", std::make_shared<UniformBuffer>(
                                               sizeof(CameraData), 0));
  }

  void update(float dt) override {
    // Logic update
    if (_isHovered) {
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

    RenderCommand::DepthTest(true);
    RenderCommand::CullFace(true);
    RenderCommand::Multisample(true);
    RenderCommand::ClearColor(math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));
    RenderCommand::Clear();

    _scene->updateEditMode(dt, _editorCameraController->getCamera());
    _frameBuffer->unBind();

    _gui->draw();
  }

 private:
  std::shared_ptr<Scene> _scene;

  math::Vector2 _sceneSize{992.0f, 558.0f};
  bool          _isHovered;

  std::unique_ptr<Gui>              _gui;
  std::shared_ptr<CameraController> _editorCameraController;

  std::shared_ptr<FrameBuffer> _frameBuffer;
};

class Editor : public Application {
 public:
  Editor() { pushLayer(new EditorLayer); }
};

Application* CreateApplication();

}  // namespace deft

#endif  // __DEFT_EDITOR_H__