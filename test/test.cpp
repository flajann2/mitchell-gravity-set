#include <iostream>
#include <compute.h>
#include <string>
#include <sstream>

int main(int ac, char* av[]) {
  Scalar<double> s {32.2};
  Coords<double, 3> c;
  string vstr(c.vec.begin(), c.vec.end());
  ostringstream cstr;
  cstr << s.value;
  
  std::cout << "Hello Test\n"
            << cstr.str() << endl
            << vstr << endl;

}
