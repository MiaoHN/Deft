#ifndef __DEFT_LOG_PANEL_H__
#define __DEFT_LOG_PANEL_H__

#include <imgui.h>

#include "log/log.h"

namespace deft {

class LogPanel {
 public:
  LogPanel();

  void clear();

  void update();

  void draw(const char* title, bool* p_open = NULL);

 private:
  std::shared_ptr<Log> _logPtr;
  ImGuiTextBuffer      _buffer;
  ImVector<int>        _lineOffsets;  // 记录换行位置
};

}  // namespace deft

#endif  // __DEFT_LOG_PANEL_H__