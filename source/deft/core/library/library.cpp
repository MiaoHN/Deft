#include "core/library/library.h"

namespace deft {

template <typename T>
std::shared_ptr<Library<T>> Library<T>::GetInstance() {
  return nullptr;
}

}  // namespace deft