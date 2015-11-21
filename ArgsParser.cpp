#include "ArgsParser.hpp"
#include <algorithm>

char* ArgsParser::getArgument(int argc, char **argv, const std::string& option) {
  char **end  = argv + argc;
  char **itOp = std::find(argv, end, option);

  if ((itOp != end) && (++itOp != end)) return *itOp;
  else return 0;
}

bool ArgsParser::existArgument(int argc, char **argv, const std::string& option) {
  char **end = argv + argc;

  return std::find(argv, end, option) != end;
}
