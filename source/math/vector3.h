#ifndef __DEFT_VECTOR3_H__
#define __DEFT_VECTOR3_H__

#include <sstream>
#include <string>

namespace deft {

namespace math {

class Vector3 {
 public:
  float x, y, z;

  Vector3() : Vector3(0) {}
  Vector3(float x_) : x(x_), y(x_), z(x_) {}
  Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

  float dot(const Vector3& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
  }
  Vector3 cross(const Vector3& vec) const {
    return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z,
                   x * vec.y - y * vec.x);
  }

  bool operator==(const Vector3& vec) {
    auto diff = *this - vec;
    return diff * diff < 1e-7;
  }

  float        length() const { return sqrt(dot(*this)); }
  friend float length(const Vector3& vec) { return vec.length(); }

  friend float operator*(const Vector3& vec1, const Vector3& vec2) {
    return vec1.dot(vec2);
  }
  friend Vector3 operator*(float k, const Vector3& vec) {
    return Vector3(vec.x * k, vec.y * k, vec.z * k);
  }
  friend Vector3 operator*(const Vector3& vec, float k) {
    return Vector3(vec.x * k, vec.y * k, vec.z * k);
  }
  friend Vector3 operator/(const Vector3& vec, float k) {
    return Vector3(vec.x / k, vec.y / k, vec.z / k);
  }
  friend Vector3 operator+(const Vector3& vec1, const Vector3& vec2) {
    return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
  }
  friend Vector3 operator-(const Vector3& vec1, const Vector3& vec2) {
    return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
  os << vec.toString();
  return os;
}

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR3_H__