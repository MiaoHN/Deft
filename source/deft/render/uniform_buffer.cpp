#include "render/uniform_buffer.h"

namespace deft {

std::unordered_map<std::string, std::shared_ptr<UniformBuffer>>
    UniformBufferLib::_map;

}  // namespace deft
