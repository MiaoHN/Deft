#ifndef __DEFT_TEST_H__
#define __DEFT_TEST_H__

#include <cstdio>

#define MSG(...) printf(__VA_ARGS__);

#define TEST_ASSERT(x)                               \
  if (!(x)) {                                        \
    MSG("ASSERTION FAILED at line: %d\n", __LINE__); \
  }

#endif  // __DEFT_TEST_H__