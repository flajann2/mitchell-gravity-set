#include <memory>
#include <iostream>
#include <compute.hpp>

using namespace std;
using namespace mgs;

template struct Scalar<>;
template struct Coords<>;
template struct Index<>;
template struct Position<>;
template struct Velocity<>;
template struct Acceleration<>;
template struct Field<>;

template <typename F, typename I>
Index<I> Field<F,I>::coords2index(Coords<F>& c) {
  cout << "**** You Rang??? ****" << endl;
  return Index<I>{};
}

template <typename F, typename I>
I& Field<F,I>::operator[](Index<I>& idx) {
  I offset = 0;
  I r = 1;
  for (auto v : idx.ijk) {
    offset += v * r;
    r *= cube_size;
  }
  return grid[offset];
}
