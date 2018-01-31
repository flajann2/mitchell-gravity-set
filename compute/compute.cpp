#include <memory>
#include <iostream>
#include <compute.h>

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

int16_t& Field::operator[](Index& idx) {
  int16_t offset = 0;
  int16_t r = 1;
  for (auto v : idx.ijk) {
    offset += v * r;
    r *= cube_size;
  }
  return grid[offset];
}


Vector Field::compute_center_of_star_mass() {
  double total_star_mass = 0.0;
  Vector center_accum;

  for (auto star : stars) {
    total_star_mass += star.mass;
    center_accum += star.position * star.mass;
  }
  return center_accum / total_star_mass;
}

void Field::render_with_callback(std::function<void(Index, Vector)> cb) {
  center_of_star_mass = compute_center_of_star_mass();
}

int16_t Field::render_single_cell(const Vector& initial_p, const Vector& initial_v) {
  auto v = initial_v;
  auto p = initial_p;
  int16_t iter = 0;

  for (iter = 0; iter < iter_limit; ++iter) {
    if ((p - center_of_star_mass).norm() > escape_radius) {
      break;
    }

    Vector a;

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
Vector Field::compute_acceleration(const Star& star, const Vector& fpm) const {
  auto r_vec = fpm - star.position;
  auto r_squared = r_vec.norm_squared();
  auto r = sqrt(r_squared);
  auto unit_vec = r_vec / r;
  auto force = (-gravitational_constant) * star.mass / r_squared;
  return unit_vec * force;
}
