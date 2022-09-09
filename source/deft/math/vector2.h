#ifndef __DEFT_VECTOR2_H__
#define __DEFT_VECTOR2_H__

#include <sstream>
#include <string>

#include "math/base.h"

namespace deft {

namespace math {

class Vector2 {
 public:
  float x, y;

  Vector2();
  Vector2(float x_);
  Vector2(float x_, float y_);

  float dot(const Vector2& vec) const;

  bool operator==(const Vector2& vec);

  float length() const;

  std::string toString() const;
};

float   length(const Vector2& vec);
float   operator*(const Vector2& vec1, const Vector2& vec2);
Vector2 operator*(float k, const Vector2& vec);
Vector2 operator*(const Vector2& vec, float k);
Vector2 operator/(const Vector2& vec, float k);
Vector2 operator+(const Vector2& vec1, const Vector2& vec2);
Vector2 operator-(const Vector2& vec1, const Vector2& vec2);

std::ostream& operator<<(std::ostream& os, const Vector2& vec);

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR2_H__