#include "declarations.h"
#include <functional>

std::function<void ()> wrapNoArgs() {
  return std::bind(noArgs);
}

std::function<void (int, double, bool)> wrapBuiltInArgs() {
  return std::bind(builtInArgs, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

std::function<void ()> wrapBuiltInArgs2() {
  return std::bind(builtInArgs, 3, 42.3, false);
}

std::function<void (const Strings&, Map)> wrapStdArgs() {
  return std::bind(stdArgs, std::placeholders::_1, std::placeholders::_2);
}

std::function<void ()> wrapStdArgs2() {
  return std::bind(stdArgs, Strings(), Map());
}

std::function<void ()> wrapNoArgsI() {
  Interface* i;
  return std::bind(&Interface::noArgs, i);
}

std::function<void (Interface* i, int, double, bool)> wrapBuiltInArgsI() {
  return std::bind(&Interface::builtInArgs, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
      std::placeholders::_4);
}

std::function<void (int, double, bool)> wrapBuiltInArgsI2() {
  Interface* i;
  return std::bind(&Interface::builtInArgs, i, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3);
}

std::function<void ()> wrapBuiltInArgsI3() {
  Interface* i;
  return std::bind(&Interface::builtInArgs, i, 3, 42.3, false);
}

std::function<void (Interface*, const Strings&, Map)> wrapStdArgsI() {
  return std::bind(&Interface::stdArgs, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

std::function<void (const Strings&, Map)> wrapStdArgsI2() {
  Interface* i;
  return std::bind(&Interface::stdArgs, i, std::placeholders::_1, std::placeholders::_2);
}

std::function<void ()> wrapStdArgsI3() {
  Interface* i;
  return std::bind(&Interface::stdArgs, i, Strings(), Map());
}
