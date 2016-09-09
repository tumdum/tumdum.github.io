#include "declarations.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>

boost::function<void ()> wrapNoArgs() {
  return boost::bind(noArgs);
}

boost::function<void (int, double, bool)> wrapBuiltInArgs() {
  return boost::bind(builtInArgs, _1, _2, _3);
}

boost::function<void ()> wrapBuiltInArgs2() {
  return boost::bind(builtInArgs, 3, 42.3, false);
}

boost::function<void (const Strings&, Map)> wrapStdArgs() {
  return boost::bind(stdArgs, _1, _2);
}

boost::function<void ()> wrapStdArgs2() {
  return boost::bind(stdArgs, Strings(), Map());
}

boost::function<void ()> wrapNoArgsI() {
  Interface* i;
  return boost::bind(&Interface::noArgs, i);
}

boost::function<void (Interface* i, int, double, bool)> wrapBuiltInArgsI() {
  return boost::bind(&Interface::builtInArgs, _1, _2, _3,
      _4);
}

boost::function<void (int, double, bool)> wrapBuiltInArgsI2() {
  Interface* i;
  return boost::bind(&Interface::builtInArgs, i, _1, _2,
      _3);
}

boost::function<void ()> wrapBuiltInArgsI3() {
  Interface* i;
  return boost::bind(&Interface::builtInArgs, i, 3, 42.3, false);
}

boost::function<void (Interface*, const Strings&, Map)> wrapStdArgsI() {
  return boost::bind(&Interface::stdArgs, _1, _2, _3);
}

boost::function<void (const Strings&, Map)> wrapStdArgsI2() {
  Interface* i;
  return boost::bind(&Interface::stdArgs, i, _1, _2);
}

boost::function<void ()> wrapStdArgsI3() {
  Interface* i;
  return boost::bind(&Interface::stdArgs, i, Strings(), Map());
}
