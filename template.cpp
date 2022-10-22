#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <tuple>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <algorithm>

#define ASSERT_EQ(a, b) \
   { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (a != b)       \
     {                 \
       std::cout << a << " != " << b << std::endl; \
       assert(0);                  \
     }                  \
     }


int _main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
