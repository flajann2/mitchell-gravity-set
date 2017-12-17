/*
 * MGS internal classes
 *
 * F is a float-like type (float or double)
 * I is an int-like type (short, int, long, etc.)
 */

#include <vector>
#include <initializer_list>
#include <cmath>

namespace mgs {

const int default_dimension= 2;

template <class F = double> struct Scalar {
  F value;
  explicit Scalar(F v) : value(v) {}
};

template <class F = double> struct Coords {
  std::vector<F> vec;
  
  Coords(int dim = default_dimension) { vec.resize(dim); }
  Coords(std::initializer_list<F> list) : vec(list) {}
};

template <class I = int> struct Index {
  std::vector<I> ijk;
  Index(std::initializer_list<I> list) : ijk(list) {}
};

template <class F = double> struct Position : public Coords<F> {
  Position(int dim = default_dimension) : Coords<F>(dim)  {}
  Position(std::initializer_list<F> list) : Coords<F>(list) {}  
};

template <class F = double> struct Velocity : public Coords<F> {
  Velocity(int dim = default_dimension) : Coords<F>(dim)  {}
  Velocity(std::initializer_list<F> list) : Coords<F>(list) {}  
};

template <class F = double> struct Acceleration : public Coords<F> {
  Acceleration(int dim = default_dimension) : Coords<F>(dim)  {}
  Acceleration(std::initializer_list<F> list) : Coords<F>(list) {}  
};

// Field of points to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
template <class F = double, class I = int> struct Field {
  Coords<F> c1; // negative-most bounding corner
  Coords<F> c2; // positive-most bounding corner
  std::vector<I> grid;

  I dimension;
  I cube_size;
  
  Field(I cs,
        I dim,
        Coords<F> nbound,
        Coords<F> pbound) : cube_size(cs),
                            dimension(dim),
                            c1(nbound),
                            c2(pbound) {
    grid.resize(std::pow(cs, dim));
  }

  // WARN: no boundary checks are done here.
  I& operator[](Index<I>& idx) {
    I offset = 0;
    I r = 1;
    for (auto v : idx.ijk) {
      offset += v * r;
      r *= cube_size;
    }
    return grid[offset];
  }

  // Convert a coordinate into an index.
  // WARN: No bounds checking is done here.
  Index<I> coords2index(Coords<F>& c) {
  }
};




} // namespace mgs
