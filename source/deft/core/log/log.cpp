#include "core/log/log.h"

namespace deft {

std::string Log::Level::ToString(L level) {
  switch (level) {
    case Info:
      return "INFO";
    case Warn:
      return "WARN";
    case Error:
      return "ERROR";
    case Fatal:
      return "FATAL";
  }
  return "UNKNOWN";
}

Log::Log() : offset(0) { _file.open("deft.log", std::ios::trunc); }

Log::~Log() { refresh(); }

void Log::log_core(Level::L level, const char* fmt, ...) {
  std::string levelStr = Level::ToString(level);
  char        str[512];
  va_list     ap;
  va_start(ap, fmt);
  vsnprintf(str, 512, fmt, ap);
  va_end(ap);
  std::stringstream ss;
  ss << "[" << levelStr << "]\t" << str;
  _logCoreStrs.push_back(ss.str());
  refresh();
}

void Log::log_client(Level::L level, const char* fmt, ...) {
  std::string levelStr = Level::ToString(level);
  char        str[512];
  va_list     ap;
  va_start(ap, fmt);
  vsnprintf(str, 512, fmt, ap);
  va_end(ap);

  std::stringstream ss;
  ss << "[" << levelStr << "]\t" << str;
  _logClientStrs.push_back(ss.str());
}

std::shared_ptr<Log> Log::Get() {
  static std::shared_ptr<Log> s_instance(new Log());
  return s_instance;
}

std::vector<std::string> Log::getClientLogStrs() {
  std::vector<std::string> result = std::vector<std::string>(
      _logClientStrs.begin() + offset, _logClientStrs.end());
  offset = _logClientStrs.size();
  return result;
}

void Log::refresh() {
  if (_file.is_open()) _file.close();
  _file.open("deft.log", std::ios::app);
  for (auto& str : _logCoreStrs) {
    _file << str << std::endl;
  }
  _logCoreStrs.clear();
  _file.close();
}

}  // namespace deft
