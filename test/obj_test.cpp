#include "obj_loader.h"
#include "test.h"

using namespace deft;

int main(int argc, char const *argv[]) {
  ObjLoader::Load("assets/model/standford-bunny.obj");
  return 0;
}
