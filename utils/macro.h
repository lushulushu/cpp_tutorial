#ifndef UTILS_MACRO_H_
#define UTILS_MACRO_H_

#include <iostream>

#define CHECK(x) \
  if (!(x)) std::cout << "Check failed at " << __FILE__ << ":" << __LINE__

#define CHECK_EQ(x, y) CHECK((x) == (y))

#endif  // UTILS_MACRO_H_
