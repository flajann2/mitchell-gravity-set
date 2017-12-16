#include <iostream>
#include <compute.h>
#include <string>
#include <sstream>

void pr_coord(auto prefix, auto c) {
 for (int v : c.vec)
   cout << prefix << ": " << v << endl;
 cout << endl;
}

int main(int ac, char* av[]) {
  Scalar<> s {32.2};
  Coords<> c {3, 2.3, 22};
  Coords<> cc;
  Position<> p {0.01, 5.53, -34.1};
  
  ostringstream cstr;
  cstr << s.value;
  
  std::cout << "Hello Test\n"
            << cstr.str() << endl;
            

  pr_coord(" c", c);
  pr_coord("cc", cc);
  pr_coord(" p", p);
}

