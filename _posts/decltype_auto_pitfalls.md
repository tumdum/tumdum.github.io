+++
date = "2015-03-06T19:07:07+02:00"
draft = false
title = "Joy of c++"

+++
```cpp
#include <type_traits>

decltype(auto) foo1() {
  int x;
  return x;
}

decltype(auto) foo2() {
  int x;
  return (x);
}

int main() {
  static_assert(std::is_same<decltype(foo1()),int>::value, "");
  static_assert(std::is_same<decltype(foo2()),int&>::value, "");
}
```
