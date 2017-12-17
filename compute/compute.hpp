/*
 * MGS internal classes
 *
 * F is a float-like type (float or double)
 * I is an int-like type (short, int, long, etc.)
 *
 * The default typenames will be instantiated by
 * the cpp. Later, we can easily add support for
 * other possibilities, but for now, we don't need.
 */

#include <vector>
#include <initializer_list>
#include <cmath>

namespace mgs {

const int default_dimension= 2;

template <typename F = double>
struct Scalar {
  F value;
  explicit Scalar(F v) : value(v) {}
};

template <typename F = double>
struct Coords {
  std::vector<F> vec;
  
  Coords(int dim = default_dimension) { vec.resize(dim); }
  Coords(std::initializer_list<F> list) : vec(list) {}
};

template <typename I = int>
struct Index {
  std::vector<I> ijk;
  Index(std::initializer_list<I> list) : ijk(list) {}
};

template <typename F = double>
struct Position : public Coords<F> {
  Position(int dim = default_dimension) : Coords<F>(dim)  {}
  Position(std::initializer_list<F> list) : Coords<F>(list) {}  
};

template <typename F = double>
struct Velocity : public Coords<F> {
  Velocity(int dim = default_dimension) : Coords<F>(dim)  {}
  Velocity(std::initializer_list<F> list) : Coords<F>(list) {}  
};

template <typename F = double>
struct Acceleration : public Coords<F> {
  Acceleration(int dim = default_dimension) : Coords<F>(dim)  {}
  Acceleration(std::initializer_list<F> list) : Coords<F>(list) {}  
};

// Field of points to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
template <typename F = double, typename I = int>
struct Field {
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
  I& operator[](Index<I>& idx); 

  // Convert a coordinate into an index.
  // WARN: No bounds checking is done here.
  Index<I> coords2index(Coords<F>& c);
};

template <typename F = double, typename I = int>
struct Star {
};


} // namespace mgs
