#ifndef __DEFT_MATH_MATRIX4_H__
#define __DEFT_MATH_MATRIX4_H__

#include <sstream>
#include <string>

#include "math/vector3.h"
#include "math/vector4.h"

namespace deft {

namespace math {

class Matrix4 {
 public:
  Matrix4();
  Matrix4(float x);
  Matrix4(float x1, float x2, float x3, float x4);

  Matrix4(float x1, float x2, float x3, float x4,     //
          float x5, float x6, float x7, float x8,     //
          float x9, float x10, float x11, float x12,  //
          float x13, float x14, float x15, float x16  //
  );
  Matrix4(const Matrix4& mat);

  float*       ptr();
  const float* ptr() const;

  Vector4&       operator[](int index);
  const Vector4& operator[](int index) const;

  std::string toString() const;

 private:
  Vector4 _col[4];
};

Matrix4 operator*(const Matrix4& mat1, const Matrix4& mat2);

Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

Matrix4 perspective(float fov, float aspect, float near, float far);

Matrix4 translate(const Matrix4& mat, const Vector3& vec);

Matrix4 scale(const Matrix4& mat, const Vector3& vec);

Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec);

}  // namespace math

}  // namespace deft

#endif  // __DEFT_MATH_MATRIX4_H__