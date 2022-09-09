#ifndef __DEFT_VECTOR3_H__
#define __DEFT_VECTOR3_H__

#include <sstream>
#include <string>

namespace deft {

namespace math {

class Vector3 {
 public:
  float x, y, z;

  Vector3();
  Vector3(float x_);
  Vector3(float x_, float y_, float z_);

  float   dot(const Vector3& vec) const;
  Vector3 cross(const Vector3& vec) const;

  float&       operator[](int index);
  const float& operator[](int index) const;

  bool operator==(const Vector3& vec) const;
  void operator+=(const Vector3& vec);

  float   operator*(const Vector3& vec2) const;
  Vector3 operator*(float k) const;
  Vector3 operator/(float k) const;
  Vector3 operator+(const Vector3& vec2) const;
  Vector3 operator-(const Vector3& vec2) const;

  Vector3&      normalized();
  const Vector3 normalized() const;

  float length() const;

  std::string toString() const;
};
Vector3 operator*(float k, const Vector3& vec);

std::ostream& operator<<(std::ostream& os, const Vector3& vec);

Vector3 normalize(Vector3 vec);
Vector3 cross(const Vector3& vec1, const Vector3& vec2);
float   dot(const Vector3& vec1, const Vector3& vec2);

float length(const Vector3& vec);

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR3_H__