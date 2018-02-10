#include <memory>
#include <iostream>
#include <compute.h>

using namespace std;
using namespace mgs;

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
void Field<T,I,P>::render_with_callback(std::function<void(Index, Position)> cb) {
  center_of_star_mass = compute_center_of_star_mass<T,I,P>(stars);
}


// so that StarField is instantiated in this library.
// FIXME: This is a duplication of StarField.
template struct Field<double, std::int16_t, struct FieldParm>;
