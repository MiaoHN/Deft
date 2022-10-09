#ifndef __DEFT_LOG_H__
#define __DEFT_LOG_H__

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace deft {

class Log {
 public:
  class Level {
   public:
    enum L {
      Info,
      Warn,
      Error,
      Fatal,
    };

    static std::string ToString(L level);
  };

  Log();
  ~Log();

  void log_core(Level::L level, const char* fmt, ...);

  void log_client(Level::L level, const char* fmt, ...);

  static std::shared_ptr<Log> Get();

  std::vector<std::string> getClientLogStrs();

 private:
  void refresh();

 private:
  std::vector<std::string> _logCoreStrs;
  std::vector<std::string> _logClientStrs;
  int                      offset;
  std::ofstream            _file;
};

}  // namespace deft

#define LOG_CORE(level, ...)   deft::Log::Get()->log_core(level, __VA_ARGS__)
#define LOG_CLIENT(level, ...) deft::Log::Get()->log_client(level, __VA_ARGS__)

#define LOG_CORE_INFO(...)  LOG_CORE(deft::Log::Level::Info, __VA_ARGS__)
#define LOG_CORE_WARN(...)  LOG_CORE(deft::Log::Level::Warn, __VA_ARGS__)
#define LOG_CORE_ERROR(...) LOG_CORE(deft::Log::Level::Error, __VA_ARGS__)
#define LOG_CORE_FATAL(...) LOG_CORE(deft::Log::Level::Fatal, __VA_ARGS__)

#define LOG_CLIENT_INFO(...)  LOG_CLIENT(deft::Log::Level::Info, __VA_ARGS__)
#define LOG_CLIENT_WARN(...)  LOG_CLIENT(deft::Log::Level::Warn, __VA_ARGS__)
#define LOG_CLIENT_ERROR(...) LOG_CLIENT(deft::Log::Level::Error, __VA_ARGS__)
#define LOG_CLIENT_FATAL(...) LOG_CLIENT(deft::Log::Level::Fatal, __VA_ARGS__)

#endif  // __DEFT_LOG_H__