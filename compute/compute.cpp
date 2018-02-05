#include <memory>
#include <iostream>
#include <compute.h>

using namespace std;
using namespace mgs::compute;

template <typename T, typename I, typename P>
Index Field<T,I,P>::coords2index(Coordinate& c) {
  cout << "**** You Rang??? ****" << endl;
  return Index{};
}

template <typename T, typename I, typename P>
T Vector<T,I,P>::norm() {
  T nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return T (sqrt(nr));
}

template <typename T, typename I, typename P>
T Vector<T,I,P>::norm_squared() {
  T nr = 0.0;
  for (auto v : vec) { nr += v * v; }
  return nr;
}

template <typename T, typename I, typename P>
Vector<T,I,P> Vector<T,I,P>::unit_vector() {
  return *this / this->norm();
}

template <typename T, typename I, typename P>
I& Field<T,I,P>::operator[](Index& idx) {
  int16_t offset = 0;
  int16_t r = 1;
  for (auto v : idx.ijk) {
    offset += v * r;
    r *= cube_size;
  }
  return grid[offset];
}

template <typename T, typename I, typename P>
Position Field<T,I,P>::compute_center_of_star_mass() {
  double total_star_mass = 0.0;
  Position center_accum;

  for (auto star : stars) {
    total_star_mass += star.mass;
    center_accum += star.position * star.mass;
  }
  return center_accum / total_star_mass;
}

template <typename T, typename I, typename P>
void Field<T,I,P>::render_with_callback(std::function<void(Index, Position)> cb) {
  center_of_star_mass = compute_center_of_star_mass();
}

template <typename T, typename I, typename P>
I Field<T,I,P>::render_single_cell(const Position& initial_p, const Velocity& initial_v) {
  auto v = initial_v;
  auto p = initial_p;
  I iter = 0;

  for (iter = 0; iter < iter_limit; ++iter) {
    if ((p - center_of_star_mass).norm() > escape_radius) {
      break;
    }

    Acceleration a;

    // acceleration due to all the stars
    for (auto star : stars) { a += compute_acceleration(star, p); }
    v += a * delta_t;
    p += v * delta_t;    
  }
  return iter;
}

/*
 * Do the Newton with the Floating Point16_t Mass and a single
 * Star. Note that r_squared is computed without squaring
 * the final result, but the sum of the squared components, so
 * we do that first, then take it's square root to save on the
 * calculations.
 *
 * TODO: This should be inlined for greater performance.
 * TODO: Also some consideration should be given for
 * TODO: more optimizations so this can run completely
 * TODO: in the L1 or L2 cache. Also, how can this be
 * TODO: restructured so this can take advantage of SMID?
 */
template <typename T, typename I, typename P>
Acceleration Field<T,I,P>::compute_acceleration(const Star& star, const Position& fpm) const {
  auto r_vec = fpm - star.position;
  auto r_squared = r_vec.norm_squared();
  auto r = sqrt(r_squared);
  auto unit_vec = r_vec / r;
  auto force = (-gravitational_constant) * star.mass / r_squared;
  return unit_vec * force;
}

// so that StarField is instantiated in this library.
// FIXME: This is a duplication of StarField.
template struct Field<double, std::int16_t, struct FieldParm>;


