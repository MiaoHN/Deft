#include "gui/log_panel.h"

#include "pch.h"

namespace deft {

LogPanel::LogPanel() {
  _logPtr = Log::Get();
  clear();
}

void LogPanel::clear() {
  _buffer.clear();
  _lineOffsets.clear();
  _lineOffsets.push_back(0);
}

void LogPanel::update() {
  int old_size = _buffer.size();

  std::vector<std::string> logs = _logPtr->getClientLogStrs();

  for (auto& msg : logs) {
    _buffer.append(msg.c_str());
    _lineOffsets.push_back(_buffer.size());
  }

  if (!ImGui::Begin("Log")) {
    ImGui::End();
    return;
  }

  // Main window

  ImGui::Separator();
  ImGui::BeginChild("scrolling", ImVec2(0, 0), false,
                    ImGuiWindowFlags_HorizontalScrollbar);

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
  const char* buf     = _buffer.begin();
  const char* buf_end = _buffer.end();

  ImGuiListClipper clipper;
  clipper.Begin(_lineOffsets.Size);
  while (clipper.Step()) {
    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd;
         line_no++) {
      const char* line_start = buf + _lineOffsets[line_no];
      const char* line_end   = (line_no + 1 < _lineOffsets.Size)
                                   ? (buf + _lineOffsets[line_no + 1] - 1)
                                   : buf_end;
      ImGui::TextUnformatted(line_start, line_end);
    }
  }
  clipper.End();

  ImGui::PopStyleVar();

  if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::EndChild();
  ImGui::End();
}

}  // namespace deft
