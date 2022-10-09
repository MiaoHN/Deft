#ifndef __DEFT_QUATERNION_H__
#define __DEFT_QUATERNION_H__

#include "core/math/matrix4.h"
#include "core/math/vector3.h"

namespace deft {

namespace math {

class Quaternion {
 public:
  float w, x, y, z;

  Quaternion(const Vector3& vec3) {
    Vector3 c =
        Vector3(cos(vec3.x * 0.5f), cos(vec3.y * 0.5f), cos(vec3.z * 0.5f));
    Vector3 s =
        Vector3(sin(vec3.x * 0.5f), sin(vec3.y * 0.5f), sin(vec3.z * 0.5f));

    w = c.x * c.y * c.z + s.x * s.y * s.z;
    x = s.x * c.y * c.z - c.x * s.y * s.z;
    y = c.x * s.y * c.z + s.x * c.y * s.z;
    z = c.x * c.y * s.z - s.x * s.y * c.z;
  }

  Matrix4 toMatrix4() {
    Matrix4 result(1.0f);
    float   qxx(x * x);
    float   qyy(y * y);
    float   qzz(z * z);
    float   qxz(x * z);
    float   qxy(x * y);
    float   qyz(y * z);
    float   qwx(w * x);
    float   qwy(w * y);
    float   qwz(w * z);

    result[0][0] = 1 - 2 * (qyy + qzz);
    result[0][1] = 2 * (qxy + qwz);
    result[0][2] = 2 * (qxz - qwy);

    result[1][0] = 2 * (qxy - qwz);
    result[1][1] = 1 - 2 * (qxx + qzz);
    result[1][2] = 2 * (qyz + qwx);

    result[2][0] = 2 * (qxz + qwy);
    result[2][1] = 2 * (qyz - qwx);
    result[2][2] = 1 - 2 * (qxx + qyy);

    return result;
  }
};

}  // namespace math

}  // namespace deft

#endif  // __DEFT_QUATERNION_H__