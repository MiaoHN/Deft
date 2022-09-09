#include "math/vector2.h"

#include "math/base.h"

namespace deft {

namespace math {

Vector2::Vector2() : Vector2(0) {}

Vector2::Vector2(float x_) : x(x_), y(x_) {}

Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

float Vector2::dot(const Vector2& vec) const { return x * vec.x + y * vec.y; }

bool Vector2::operator==(const Vector2& vec) {
  auto diff = *this - vec;
  return diff * diff < 1e-7;
}

float Vector2::length() const { return sqrt(dot(*this)); }

float length(const Vector2& vec) { return vec.length(); }

float operator*(const Vector2& vec1, const Vector2& vec2) {
  return vec1.dot(vec2);
}
Vector2 operator*(float k, const Vector2& vec) {
  return Vector2(vec.x * k, vec.y * k);
}
Vector2 operator*(const Vector2& vec, float k) {
  return Vector2(vec.x * k, vec.y * k);
}
Vector2 operator/(const Vector2& vec, float k) {
  return Vector2(vec.x / k, vec.y / k);
}
Vector2 operator+(const Vector2& vec1, const Vector2& vec2) {
  return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
}
Vector2 operator-(const Vector2& vec1, const Vector2& vec2) {
  return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
}

std::string Vector2::toString() const {
  std::stringstream ss;
  ss << "(" << x << ", " << y << ")";
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
  os << vec.toString();
  return os;
}

}  // namespace math

}  // namespace deft
