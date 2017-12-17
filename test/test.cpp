#include <iostream>
#include <compute.hpp>
#include <string>
#include <sstream>

using namespace std;
using namespace mgs;

void pr_coord(auto prefix, auto c) {
 for (int v : c.vec)
   cout << prefix << ": " << v << endl;
 cout << endl;
}

void test_field() {
  Coords<> c {0.44, -0.95, 1};
  Field<> f(32, 3, Coords<>{-1,-1,-1}, Coords<>{1,1,1});
  cout << "cube_size " << f.cube_size << endl;
  cout << "actual size " << f.grid.size() << endl;
  for (auto k = 0; k < f.cube_size; ++k) {
    for (auto j = 0; j < f.cube_size; ++j) {
      for (auto i = 0; i < f.cube_size; ++i) {
        Index<> idx {i, j, k};
        f[idx] = i * j * k;
        if (f[idx] != i * j * k) {
          cout << "*** ERR: " << f[idx] << " != " << (i * j * k) << endl;
        }
      }
    }
  }
  
  f.coords2index(c);
}

int main(int ac, char* av[]) {
  Scalar<> s {32.2};
  Coords<> c {3, 2.3, 22};
  Coords<> cc;
  Position<> p {0.01, 5.53, -34.1};
  
  ostringstream cstr;
  cstr << s.value;
  
  cout << "Hello Test\n"
            << cstr.str() << endl;
            

  pr_coord(" c", c);
  pr_coord("cc", cc);
  pr_coord(" p", p);

  test_field();
  cout << "DONE" << endl;
}

