#ifndef __DEFT_WINDOW_H__
#define __DEFT_WINDOW_H__

#include <memory>
#include <string>

#include "render/graphic_context.h"

struct GLFWwindow;

namespace deft {

class Window {
 public:
  Window(int width, int height, const std::string& title);
  ~Window();

  int getWidth() const;
  int getHeight() const;

  bool isClosed() const;
  void setClose(bool flag);

  GLFWwindow* getHandler() const;

  std::string getTitle() const;
  void        setTitle(const std::string& title);

  void tick() const;

 private:
  GLFWwindow* _window;

  std::unique_ptr<GraphicContext> _context;

  int         _width;
  int         _height;
  std::string _title;
};

}  // namespace deft

#endif  // __DEFT_WINDOW_H__