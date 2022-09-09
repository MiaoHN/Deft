#include "math/vector3.h"

#include "math/base.h"

namespace deft {

namespace math {

Vector3::Vector3() : Vector3(0) {}

Vector3::Vector3(float x_) : x(x_), y(x_), z(x_) {}

Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

float Vector3::dot(const Vector3& vec) const {
  return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(const Vector3& vec) const {
  return {
      y * vec.z - z * vec.y,  //
      z * vec.x - x * vec.z,  //
      x * vec.y - y * vec.x   //
  };
}

bool Vector3::operator==(const Vector3& vec) const {
  auto diff = *this - vec;
  return diff * diff < 1e-7;
}

float& Vector3::operator[](int index) { return *(&x + index); }

const float& Vector3::operator[](int index) const { return *(&x + index); }

Vector3& Vector3::normalized() {
  float len = length();
  x /= len;
  y /= len;
  z /= len;

  return *this;
}

const Vector3 Vector3::normalized() const {
  Vector3 vec(x, y, z);
  vec.normalized();
  return vec;
}

float Vector3::length() const { return sqrt(dot(*this)); }

void Vector3::operator+=(const Vector3& vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
}

std::string Vector3::toString() const {
  std::stringstream ss;
  ss << "(" << x << ", " << y << ", " << z << ")";
  return ss.str();
}

float Vector3::operator*(const Vector3& vec2) const { return dot(vec2); }

Vector3 operator*(float k, const Vector3& vec) {
  return {vec.x * k, vec.y * k, vec.z * k};
}

Vector3 Vector3::operator*(float k) const { return {x * k, y * k, z * k}; }

Vector3 Vector3::operator/(float k) const { return {x / k, y / k, z / k}; }

Vector3 Vector3::operator+(const Vector3& vec2) const {
  return {x + vec2.x, y + vec2.y, z + vec2.z};
}

Vector3 Vector3::operator-(const Vector3& vec2) const {
  return {x - vec2.x, y - vec2.y, z - vec2.z};
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
  os << vec.toString();
  return os;
}

Vector3 normalize(Vector3 vec) { return vec.normalized(); }

Vector3 cross(const Vector3& vec1, const Vector3& vec2) {
  return vec1.cross(vec2);
}

float dot(const Vector3& vec1, const Vector3& vec2) { return vec1.dot(vec2); }

float length(const Vector3& vec) { return vec.length(); }

}  // namespace math

}  // namespace deft