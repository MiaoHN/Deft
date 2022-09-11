#ifndef __DEFT_OBJ_LOADER_H__
#define __DEFT_OBJ_LOADER_H__

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "log/log.h"
#include "render/model.h"

namespace deft {

class ObjLoader {
 public:
  static std::shared_ptr<Model> Load(const std::string& path) {
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
      LOG_CLIENT_ERROR("ObjLoader::Load Failed to open file '%s'",
                       path.c_str());
      return nullptr;
    }
    int lineNumber = 0;
    while (!file.eof()) {
      std::string line;
      std::getline(file, line);
      if (line[0] == '#') continue;
      if (line[0] == 'v') {
        // 顶点
        float v1, v2, v3;
        sscanf(line.c_str(), "v %f %f %f", &v1, &v2, &v3);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
      }
      if (line[0] == 'f') {
        // 索引
        unsigned int u1, u2, u3;
        sscanf(line.c_str(), "f %u %u %u", &u1, &u2, &u3);
        indices.push_back(u1 - 1);
        indices.push_back(u2 - 1);
        indices.push_back(u3 - 1);
      }
      lineNumber++;
    }
    std::vector<BufferElement> layout = {{"aPos", ElementType::Float3}};

    return std::make_shared<Model>(vertices, layout, indices);
  }
};

}  // namespace deft

#endif  // __DEFT_OBJ_LOADER_H__