#ifndef __DEFT_MATH_MATRIX4_H__
#define __DEFT_MATH_MATRIX4_H__

namespace deft {

namespace math {

class Matrix4 {
 public:
  Matrix4() : Matrix4(0) {}
  Matrix4(float x) : Matrix4(x, x, x, x) {}
  Matrix4(float x1, float x2, float x3, float x4) {
    _data[0][0] = x1;
    _data[1][1] = x2;
    _data[2][2] = x3;
    _data[3][3] = x4;
  }

  Matrix4(float x1, float x2, float x3, float x4,     //
          float x5, float x6, float x7, float x8,     //
          float x9, float x10, float x11, float x12,  //
          float x13, float x14, float x15, float x16  //
  ) {
    _data[0][0] = x1;
    _data[0][1] = x2;
    _data[0][2] = x3;
    _data[0][3] = x4;
    _data[1][0] = x5;
    _data[1][1] = x6;
    _data[1][2] = x7;
    _data[1][3] = x8;
    _data[2][0] = x9;
    _data[2][1] = x10;
    _data[2][2] = x11;
    _data[2][3] = x12;
    _data[3][0] = x13;
    _data[3][1] = x14;
    _data[3][2] = x15;
    _data[3][3] = x16;
  }

  Matrix4(const Matrix4& mat) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        _data[i][j] = mat[i][j];
      }
    }
  }

  float*       operator[](int index) { return _data[index]; }
  const float* operator[](int index) const { return _data[index]; }

 private:
  float _data[4][4];
};

}  // namespace math

}  // namespace deft

#endif  // __DEFT_MATH_MATRIX4_H__