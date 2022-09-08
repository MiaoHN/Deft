#ifndef __DEFT_VECTOR4_H__
#define __DEFT_VECTOR4_H__

#include <sstream>
#include <string>

namespace deft {

namespace math {

class Vector4 {
 public:
  float x, y, z, w;

  Vector4() : Vector4(0) {}
  Vector4(float x_) : x(x_), y(x_), z(x_), w(x_) {}
  Vector4(float x_, float y_, float z_, float w_)
      : x(x_), y(y_), z(z_), w(w_) {}

  float dot(const Vector4& vec) const {
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
  }

  bool operator==(const Vector4& vec) {
    auto diff = *this - vec;
    return diff * diff < 1e-7;
  }

  float        length() const { return sqrt(dot(*this)); }
  friend float length(const Vector4& vec) { return vec.length(); }

  friend float operator*(const Vector4& vec1, const Vector4& vec2) {
    return vec1.dot(vec2);
  }
  friend Vector4 operator*(float k, const Vector4& vec) {
    return Vector4(vec.x * k, vec.y * k, vec.z * k, vec.w * k);
  }
  friend Vector4 operator*(const Vector4& vec, float k) {
    return Vector4(vec.x * k, vec.y * k, vec.z * k, vec.w * k);
  }
  friend Vector4 operator/(const Vector4& vec, float k) {
    return Vector4(vec.x / k, vec.y / k, vec.z / k, vec.w / k);
  }
  friend Vector4 operator+(const Vector4& vec1, const Vector4& vec2) {
    return Vector4(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z,
                   vec1.w + vec2.w);
  }
  friend Vector4 operator-(const Vector4& vec1, const Vector4& vec2) {
    return Vector4(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z,
                   vec1.w - vec2.w);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
    return ss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
  os << vec.toString();
  return os;
}

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR4_H__