#include "core/math/matrix4.h"

#include "core/math/base.h"
#include "pch.h"

namespace deft {

namespace math {

Matrix4::Matrix4() : Matrix4(0) {}
Matrix4::Matrix4(float x) : Matrix4(x, x, x, x) {}
Matrix4::Matrix4(float x1, float x2, float x3, float x4)
    : Matrix4(x1, 0, 0, 0,  //
              0, x2, 0, 0,  //
              0, 0, x3, 0,  //
              0, 0, 0, x4) {}

Matrix4::Matrix4(float x1, float x2, float x3, float x4,     //
                 float x5, float x6, float x7, float x8,     //
                 float x9, float x10, float x11, float x12,  //
                 float x13, float x14, float x15, float x16  //
) {
  _col[0][0] = x1;
  _col[0][1] = x2;
  _col[0][2] = x3;
  _col[0][3] = x4;
  _col[1][0] = x5;
  _col[1][1] = x6;
  _col[1][2] = x7;
  _col[1][3] = x8;
  _col[2][0] = x9;
  _col[2][1] = x10;
  _col[2][2] = x11;
  _col[2][3] = x12;
  _col[3][0] = x13;
  _col[3][1] = x14;
  _col[3][2] = x15;
  _col[3][3] = x16;
}

Matrix4::Matrix4(const Matrix4& mat) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      _col[i][j] = mat[i][j];
    }
  }
}

float* Matrix4::ptr() { return &(_col[0].x); }

const float* Matrix4::ptr() const { return &_col[0][0]; }

Matrix4 operator*(const Matrix4& mat1, const Matrix4& mat2) {
  Vector4 srcA0 = mat1[0];
  Vector4 srcA1 = mat1[1];
  Vector4 srcA2 = mat1[2];
  Vector4 srcA3 = mat1[3];
  Vector4 srcB0 = mat2[0];
  Vector4 srcB1 = mat2[1];
  Vector4 srcB2 = mat2[2];
  Vector4 srcB3 = mat2[3];

  Matrix4 result;
  result[0] =
      srcA0 * srcB0[0] + srcA1 * srcB0[1] + srcA2 * srcB0[2] + srcA3 * srcB0[3];
  result[1] =
      srcA0 * srcB1[0] + srcA1 * srcB1[1] + srcA2 * srcB1[2] + srcA3 * srcB1[3];
  result[2] =
      srcA0 * srcB2[0] + srcA1 * srcB2[1] + srcA2 * srcB2[2] + srcA3 * srcB2[3];
  result[3] =
      srcA0 * srcB3[0] + srcA1 * srcB3[1] + srcA2 * srcB3[2] + srcA3 * srcB3[3];
  return result;
}

Vector4& Matrix4::operator[](int index) { return _col[index]; }
const Vector4& Matrix4::operator[](int index) const { return _col[index]; }

std::string Matrix4::toString() const {
  std::stringstream ss;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ss << _col[i][j] << "\t";
    }
    ss << std::endl;
  }
  return ss.str();
}

Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
  Vector3 f(normalize(center - eye));
  Vector3 s(normalize(cross(f, up)));
  Vector3 u(normalize(cross(s, f)));

  Matrix4 result(1.0f);
  result[0][0] = s.x;
  result[1][0] = s.y;
  result[2][0] = s.z;
  result[0][1] = u.x;
  result[1][1] = u.y;
  result[2][1] = u.z;
  result[0][2] = -f.x;
  result[1][2] = -f.y;
  result[2][2] = -f.z;
  result[3][0] = -dot(s, eye);
  result[3][1] = -dot(u, eye);
  result[3][2] = dot(f, eye);
  return result;
}

Matrix4 perspective(float fov, float aspect, float near, float far) {
  float tanHalf = tan(fov / 2.0f);

  Matrix4 result(0.0f);
  result[0][0] = 1.0f / (aspect * tanHalf);
  result[1][1] = 1.0f / tanHalf;
  result[2][2] = -(far + near) / (far - near);
  result[2][3] = -1.0f;
  result[3][2] = -(2.0f * far * near) / (far - near);
  return result;
}

Matrix4 translate(const Matrix4& mat, const Vector3& vec) {
  Matrix4 result(mat);
  result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
  return result;
}

Matrix4 scale(const Matrix4& mat, const Vector3& vec) {
  Matrix4 result;
  result[0] = mat[0] * vec[0];
  result[1] = mat[1] * vec[1];
  result[2] = mat[2] * vec[2];
  result[3] = mat[3];
  return result;
}

Matrix4 rotate(const Matrix4& mat, float angle, const Vector3& vec) {
  float a = angle;
  float c = cos(a);
  float s = sin(a);

  Vector3 axis(normalize(vec));
  Vector3 temp((1.0 - c) * axis);

  Matrix4 rot;
  rot[0][0] = c + temp[0] * axis[0];
  rot[0][1] = temp[0] * axis[1] + s * axis[2];
  rot[0][2] = temp[0] * axis[2] - s * axis[1];

  rot[1][0] = temp[1] * axis[0] - s * axis[2];
  rot[1][1] = c + temp[1] * axis[1];
  rot[1][2] = temp[1] * axis[2] + s * axis[0];

  rot[2][0] = temp[2] * axis[0] + s * axis[1];
  rot[2][1] = temp[2] * axis[1] - s * axis[0];
  rot[2][2] = c + temp[2] * axis[2];

  Matrix4 Result;
  Result[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
  Result[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
  Result[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
  Result[3] = mat[3];
  return Result;
}

bool decomposeTransform(const Matrix4& transform, Vector3& translation,
                        Vector3& rotation, Vector3& scale) {
  Matrix4 localMatrix(transform);

  if (localMatrix[3][3] < 1e-7) {
    return false;
  }

  if ((localMatrix[0][3] < 1e-7) || (localMatrix[1][3] < 1e-7) ||
      (localMatrix[2][3] < 1e-7)) {
    localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = 0;
    localMatrix[3][3]                                         = 1;
  }

  translation    = Vector3(localMatrix[3]);
  localMatrix[3] = Vector4(0, 0, 0, localMatrix[3].w);

  Vector3 row[3], pdum3;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      row[i][j] = localMatrix[i][j];
    }
  }

  scale.x = row[0].length();
  row[0]  = normalize(row[0]);
  scale.y = row[1].length();
  row[1]  = normalize(row[1]);
  scale.z = row[2].length();
  row[2]  = normalize(row[2]);

  rotation.y = asin(-row[0][2]);
  if (cos(rotation.y) != 0) {
    rotation.x = atan2(row[1][2], row[2][2]);
    rotation.z = atan2(row[0][1], row[0][0]);
  } else {
    rotation.x = atan2(-row[2][0], row[1][1]);
    rotation.z = 0;
  }

  return true;
}

}  // namespace math

}  // namespace deft
