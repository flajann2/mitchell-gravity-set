#include <iostream>
#include <compute>
#include <marching_tetrahedra>
#include <string>
#include <sstream>

using namespace std;
using namespace mgs;

void pr_coord(const string& prefix, const Position& c) {
 for (int v : c.vec)
   cout << prefix << ": " << v << '\n';
 cout << '\n';
}

void test_field() {
  Coordinate c {0.44, -0.95, 1};
  StarField f(Coordinate{-1,-1,-1}, Coordinate{1,1,1}, 32, 3);
  cout << "cube_size " << f.cube_size << '\n';
  cout << "actual size " << f.grid.size() << '\n';
  for (auto k = 0; k < f.cube_size; ++k) {
    for (auto j = 0; j < f.cube_size; ++j) {
      for (auto i = 0; i < f.cube_size; ++i) {
        Index idx {i, j, k};
        f[idx] = i * j * k;
        if (f[idx] != i * j * k) {
          cout << "*** ERR: " << f[idx] << " != " << (i * j * k) << '\n';
        }
      }
    }
  }

  cout << f << '\n';
  
  f.coords2index(c);
}

void test_math_on_Vector() {
  Position p1 {-1, 1, 0};
  Position p2 {1, -1, 2};

  cout << "math on Vector: " << p1 << " and " << p2 << '\n';
  Position padded = p1 + p2;
  Position psubbed = p1 - p2;
  Position doub = p1 * 2.0;
  Position halved = p1 / 2.0;
  
  cout << "results:" << '\n';
  cout << "added: " << padded << '\n';
  cout << "subbed: " << psubbed << '\n';
  cout << "p1 * 2: " << doub << '\n';
  cout << "p1 / 2: " << halved << '\n';
}

int main(int ac, char* av[]) {
  double s = 32.2;
  Position c {3, 2.3, 22};
  Position cc;
  Position p {0.01, 5.53, -34.1};
  
  ostringstream cstr;
  cstr << s;
  
  cout << "Hello Test\n"
            << cstr.str() << '\n';
            

  pr_coord(" c", c);
  pr_coord("cc", cc);
  pr_coord(" p", p);

  test_field();
  test_math_on_Vector();
  
  cout << "DONE" << '\n';
}

