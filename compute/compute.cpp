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

template <typename F>
F Coords<F>::norm() {
  F nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return sqrt(nr);
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

template <typename F, typename I>
void Field<F,I>::render_with_callback(std::function<void(Index<I>, Coords<F>)> cb) {
}

template <typename F, typename I>
I Field<F,I>::render_single_cell(Position<F> initial_p, Velocity<F> initial_v) {
  Acceleration<F> a;
  auto &p = initial_p;
  auto &v = initial_v;

  // acceleration
}

template <typename F, typename I>
F Field<F,I>::compute_newton_g(const Star<F,I>& star, const Position<F>& fpm) {
}
