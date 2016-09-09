#include "declarations.h"
#include <boost/function.hpp>

boost::function<void()> wrapNoArgs() {
  return []() { noArgs(); };
}

boost::function<void(int, double, bool)> wrapBuiltInArgs() {
  return [](int a, double b, bool c) { builtInArgs(a, b, c); };
}

boost::function<void ()> wrapBuiltInArgs2() {
  return []() { builtInArgs(3, 42.3, false); };
}

boost::function<void (const Strings&, Map)> wrapStdArgs() {
  return [](const Strings& a, Map b) { stdArgs(a, b); };
}

boost::function<void ()> wrapStdArgs2() {
  return []() { Strings s; Map m; stdArgs(s, m); };
}

boost::function<void ()> wrapNoArgsI() {
  Interface* i;
  return [i]() { i->noArgs(); };
}

boost::function<void (Interface*, int, double, bool)> wrapBuiltInArgsI() {
  return [] (Interface* a, int b, double c, bool d) { a->builtInArgs(b, c, d); };
}

boost::function<void (int, double, bool)> wrapBuiltInArgsI2() {
  Interface* i;
  return [i](int a, double b, bool c) { i->builtInArgs(a, b, c); };
}

boost::function<void ()> wrapBuiltInArgsI3() {
  Interface* i;
  return [i]() { i->builtInArgs(3, 42.3, false); };
}

boost::function<void (Interface* , const Strings&, Map)> wrapStdArgsI() {
  return [](Interface* a, const Strings& b, Map c) { a->stdArgs(b, c); };
}

boost::function<void (const Strings&, Map)> wrapStdArgsI2() {
  Interface* i;
  return [i](const Strings& a, Map b) { i->stdArgs(a, b); };
}

boost::function<void ()> wrapStdArgsI3() {
  Interface* i;
  return [i]() { Strings a; Map b; i->stdArgs(a, b); };
}
