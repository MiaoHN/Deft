#ifndef __DEFT_VECTOR4_H__
#define __DEFT_VECTOR4_H__

#include <sstream>
#include <string>

namespace deft {

namespace math {

class Vector4 {
 public:
  float x, y, z, w;

  Vector4();
  Vector4(float x_);
  Vector4(float x_, float y_, float z_, float w_);

  float&       operator[](int index);
  const float& operator[](int index) const;

  float dot(const Vector4& vec) const;

  bool operator==(const Vector4& vec);

  float length() const;

  std::string toString() const;
};

float   length(const Vector4& vec);
float   operator*(const Vector4& vec1, const Vector4& vec2);
Vector4 operator*(float k, const Vector4& vec);
Vector4 operator*(const Vector4& vec, float k);
Vector4 operator/(const Vector4& vec, float k);
Vector4 operator+(const Vector4& vec1, const Vector4& vec2);
Vector4 operator-(const Vector4& vec1, const Vector4& vec2);

std::ostream& operator<<(std::ostream& os, const Vector4& vec);

}  // namespace math

}  // namespace deft

#endif  // __DEFT_VECTOR4_H__