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
Scalar<F> Coords<F>::norm() {
  F nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return Scalar<F>(sqrt(nr));
}

template <typename F>
Scalar<F> Coords<F>::norm_squared() {
  Scalar<F> nr {0.0};
  for (auto v : vec) { nr.value += v * v; }
  return nr;
}

template <typename F>
Coords<F> Coords<F>::unit_vector() {
  return *this / this->norm();
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

/*
 * Do the Newton with the Floating Point Mass and a single
 * Star.
 * TODO: This should be inlined for greater performance.
 * TODO: Also some consideration should be given for
 * TODO: more optimizations so this can run completely
 * TODO: in the L1 or L2 cache. Also, how can this be
 * TODO: restructured so this can take advantage of SMID?
 */
template <typename F, typename I>
F Field<F,I>::compute_newton_g(const Star<F,I>& star,
                               const Position<F>& fpm) {
  //auto r = (fpm - star.position).norm_squared();
}

