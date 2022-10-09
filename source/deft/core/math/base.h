#ifndef __DEFT_MATH_BASE_H__
#define __DEFT_MATH_BASE_H__

#include <cmath>

namespace deft {

namespace math {

inline float sqrt(float value) { return ::sqrt(value); }
inline float tan(float angle) { return ::tan(angle); }
inline float radians(float angle) { return angle / 180.0f * 3.1415926535f; }

}  // namespace math

}  // namespace deft

#endif  // __DEFT_MATH_BASE_H__