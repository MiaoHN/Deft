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

  Vector2() : Vector2(0) {}
  Vector2(float x_) : x(x_), y(x_) {}
  Vector2(float x_, float y_) : x(x_), y(y_) {}

  float dot(const Vector2& vec) const { return x * vec.x + y * vec.y; }

  bool operator==(const Vector2& vec) {
    auto diff = *this - vec;
    return diff * diff < 1e-7;
  }

  float        length() const { return sqrt(dot(*this)); }
  friend float length(const Vector2& vec) { return vec.length(); }

  friend float operator*(const Vector2& vec1, const Vector2& vec2) {
    return vec1.dot(vec2);
  }
  friend Vector2 operator*(float k, const Vector2& vec) {
    return Vector2(vec.x * k, vec.y * k);
  }
  friend Vector2 operator*(const Vector2& vec, float k) {
    return Vector2(vec.x * k, vec.y * k);
  }
  friend Vector2 operator/(const Vector2& vec, float k) {
    return Vector2(vec.x / k, vec.y / k);
  }
  friend Vector2 operator+(const Vector2& vec1, const Vector2& vec2) {
    return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
  }
  friend Vector2 operator-(const Vector2& vec1, const Vector2& vec2) {
    return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
  os << vec.toString();
  return os;
}

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR2_H__