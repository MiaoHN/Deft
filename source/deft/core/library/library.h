#ifndef __DEFT_LIBRARY_H__
#define __DEFT_LIBRARY_H__

#include <memory>
#include <string>
#include <unordered_map>

namespace deft {

template <typename T>
class Library {
 public:
  std::shared_ptr<T> get(const std::string& name) {
    if (_map.find(name) == _map.end()) return nullptr;
    return _map[name];
  }

  bool add(const std::string& name, const std::shared_ptr<T>& value) {
    if (_map.find(name) != _map.end()) return false;
    _map[name] = value;
    return true;
  }

  static std::shared_ptr<Library<T>> GetInstance();

 private:
  std::unordered_map<std::string, std::shared_ptr<T>> _map;
};

}  // namespace deft

#endif  // __DEFT_LIBRARY_H__