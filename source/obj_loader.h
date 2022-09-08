#ifndef __DEFT_OBJ_LOADER_H__
#define __DEFT_OBJ_LOADER_H__

#include <fstream>
#include <iostream>
#include <string>

namespace deft {

class ObjLoader {
 public:
  static void Load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
      // TODO 处理文件不存在
      return;
    }
    int lineNumber = 0;
    while (!file.eof()) {
      std::string line;
      std::getline(file, line);
      lineNumber++;
    }
    std::cout << "Total line: " << lineNumber << std::endl;
  }
};

}  // namespace deft

#endif  // __DEFT_OBJ_LOADER_H__