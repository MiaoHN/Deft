#ifndef __DEFT_WINDOW_H__
#define __DEFT_WINDOW_H__

#include <string>

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

  void pollEvents() const;

 private:
  GLFWwindow* _window;

  int         _width;
  int         _height;
  std::string _title;
};

}  // namespace deft

#endif  // __DEFT_WINDOW_H__