#include <iostream>

using namespace std;

class ArgsParser{
public:
  static char* getArgument(int, char**, const string&);

  static bool existArgument(int, char**, const string&);
};
