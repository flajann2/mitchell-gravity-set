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
#include <functional>

namespace mgs {

const int default_dimension = 2;
const int untouched = -1;

template <typename F = double>
struct Scalar {
  F value;
  explicit Scalar(F v) : value(v) {}
};

template <typename F>
std::ostream &operator<<(std::ostream &os, Scalar<F> const &s) {
  os << "Scalar[ " << s.value << "]";
  return os;
}

template <typename I = int>
struct Index {
  std::vector<I> ijk;
  Index(std::initializer_list<I> list) : ijk(list) {}
};

template <typename I>
std::ostream &operator<<(std::ostream &os, Index<I> const &idx) {
  os << "Index[ ";
  for (auto i : idx.vec) { os << i << " "; }
  os << "]";
  return os;
}

template <typename F = double>
struct Coords {
  std::vector<F> vec;
  
  Coords(int dimension = default_dimension) { vec.resize(dimension, 0.0); }
  Coords(std::initializer_list<F> list) : vec(list) {}
 
  F norm();

 protected:
  template <typename T>
  T add(const T& other) {
    T result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) {
      result.vec[i] = vec[i] + other.vec[i];
    }
    return result;
  }

  template <typename T>
  T subtract(const T& other) {
    T result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) {
      result.vec[i] = vec[i] - other.vec[i];
    }
    return result;
  }

 public:
  virtual Coords<F> operator+(const Coords<F>& other) { return add(other); }
  virtual Coords<F> operator-(const Coords<F>& other) { return subtract(other); }
};

template <typename F>
std::ostream &operator<<(std::ostream &os, Coords<F> const &c) {
  os << "Coords[ ";
  for (auto v : c.vec) { os << v << " ";  }
  os << "]";
  return os;
}

template <typename F = double>
struct Position : public Coords<F> {
  Position(int dim = default_dimension) : Coords<F>(dim)  {}
  Position(std::initializer_list<F> list) : Coords<F>(list) {} 

  virtual Position<F> operator+(const Position<F>& other) { return Coords<F>::add(other); }
  virtual Position<F> operator-(const Position<F>& other) { return Coords<F>::subtract(other); }
};

template <typename F = double>
struct Velocity : public Coords<F> {
  Velocity(int dim = default_dimension) : Coords<F>(dim)  {}
  Velocity(std::initializer_list<F> list) : Coords<F>(list) {}  

  virtual Velocity<F> operator+(const Velocity<F>& other) { return Coords<F>::add(other); }
  virtual Velocity<F> operator-(const Velocity<F>& other) { return Coords<F>::subtract(other); }
};

template <typename F = double>
struct Acceleration : public Coords<F> {
  Acceleration(int dim = default_dimension) : Coords<F>(dim)  {}
  Acceleration(std::initializer_list<F> list) : Coords<F>(list) {}  

  virtual Acceleration<F> operator+(const Acceleration<F>& other) { return Coords<F>::add(other); }
  virtual Acceleration<F> operator-(const Acceleration<F>& other) { return Coords<F>::subtract(other); }
};

template <typename F = double, typename I = int>
struct Star {
  F mass;
  Position<F> position;

  Star(F m, Position<F> pos) : mass(m), position(pos) {}
};

template <typename F, typename I>
std::ostream &operator<<(std::ostream &os, Star<F,I> const &star) {
  os << "Star[";
  os << " mass:" << star.mass;
  os << " position:" << star.position;
  os << " ]";
  return os;
}

// Field of points to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
template <typename F = double, typename I = int>
struct Field {
  Coords<F> c1; // negative-most bounding corner
  Coords<F> c2; // positive-most bounding corner

  std::vector<I> grid;
  std::vector<Star<F,I>> stars;
  
  I cube_size;
  I dimension;
  I iter_limit;
  
  F gravitational_constant;
  F escape_radius;
  F delta_t;
  
  Field(Coords<F> nbound,
        Coords<F> pbound,

        I cs = 1024,
        I dim = 2,
        I iteration_limit = 1024,
        F grav_constant = 1.0,
        F escape_r = 2.0,
        F delta_time = 0.1) : c1(nbound),
                              c2(pbound),
                              cube_size(cs),
                              dimension(dim),
                              iter_limit(iteration_limit),
                              gravitational_constant(grav_constant),
                              escape_radius(escape_r),
                              delta_t(delta_time) {
    I backfill = untouched;
    grid.resize(std::pow(cs, dim), backfill);
  }

  // WARN: no boundary checks are done here.
  I& operator[](Index<I>& idx); 

  // Convert a coordinate into an index.
  // WARN: No bounds checking is done here.
  Index<I> coords2index(Coords<F>& c);
  void render_with_callback(std::function<void(Index<I>, Coords<F>)> cb);

 private:
  I render_single_cell(Position<F> initial_p, Velocity<F> initial_v);
  F compute_newton_g(const Star<F,I>& star, const Position<F>& fpm);
};

template <typename F, typename I>
std::ostream &operator<<(std::ostream &os, Field<F,I> const &f) {
  os << "Field[";
  os << " c1:" << f.c1;
  os << " c2:" << f.c2;
  os << " cube_size:" << f.cube_size;
  os << " dimension:" << f.dimension;
  os << " iter_limit:" << f.iter_limit;
  os << " gravitational_constant:" << f.gravitational_constant;
  os << " escappe_radius:" << f.escape_radius;
  os << " delta_t:" << f.delta_t;

  os << "Stars[ ";
  for (auto star : f.stars) {
    os << star << " ";
  }
  os << "]";

  os << "]"; 
  return os;
}

} // namespace mgs
