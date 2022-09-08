#include "math/math.h"

#include <iostream>

#include "test.h"

using namespace deft::math;

int main(int argc, char const *argv[]) {
  Vector3 vec1(0, 1, 3);
  Vector3 vec2(0, 1, 3);
  Vector2 vec3(1, 0);
  TEST_ASSERT(vec1 == vec2);
  std::cout << vec3 << std::endl;
  std::cout << "vec1 = " << vec1 << ", length = " << vec1.length() << std::endl;

  return 0;
}
