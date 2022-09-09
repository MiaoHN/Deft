#include "test.h"
#include "util/obj_loader.h"

using namespace deft;

int main(int argc, char const *argv[]) {
  ObjLoader::Load("assets/model/standford-bunny.obj");
  return 0;
}
