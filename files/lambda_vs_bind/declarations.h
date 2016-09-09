#include <string>
#include <vector>
#include <map>
#include <set>

using Strings = std::vector<std::string>;
using Map = std::map<std::string, std::set<int>>;

void noArgs();
void builtInArgs(int, double, bool);
void stdArgs(const Strings& , Map);

struct Interface {
  virtual ~Interface() {}
  virtual void noArgs() = 0;
  virtual void builtInArgs(int, double, bool) = 0;
  virtual void stdArgs(const Strings& , Map) = 0;
};
