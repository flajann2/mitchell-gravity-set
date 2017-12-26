#include <memory>
#include <iostream>
#include <compute.hpp>

using namespace std;
using namespace mgs;

Index Field::coords2index(Vector& c) {
  cout << "**** You Rang??? ****" << endl;
  return Index{};
}

double Vector::norm() {
  double nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return double(sqrt(nr));
}

double Vector::norm_squared() {
  double nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return nr;
}

Vector Vector::unit_vector() {
  return *this / this->norm();
}

int& Field::operator[](Index& idx) {
  int offset = 0;
  int r = 1;
  for (auto v : idx.ijk) {
    offset += v * r;
    r *= cube_size;
  }
  return grid[offset];
}

void Field::render_with_callback(std::function<void(Index, Vector)> cb) {
}

int Field::render_single_cell(Vector initial_p, Vector initial_v) {
  Vector a;
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
double Field::compute_newton_g(const Star& star, const Vector& fpm) {
  //auto r = (fpm - star.position).norm_squared();
}
