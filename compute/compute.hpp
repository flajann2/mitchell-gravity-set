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

const int default_dimension= 2;
const int untouched = -1;

template <typename F = double>
struct Scalar {
  F value;
  explicit Scalar(F v) : value(v) {}
};

template <typename I = int>
struct Index {
  std::vector<I> ijk;
  Index(std::initializer_list<I> list) : ijk(list) {}
};

template <typename F = double>
struct Coords {
  int dim;
  std::vector<F> vec;
  
  Coords(int dimension = default_dimension) : dim(dimension) { vec.resize(dim, 0.0); }
  Coords(std::initializer_list<F> list) : vec(list) {}
 
  F norm();

  template <typename T>
  T add(const T& other) {
    T result;
    for (auto i = 0; i < dim; ++i) {
      result.vec[i] = vec[i] + other.vec[i];
    }
    return result;
  }

 public:
  virtual Coords<F> operator+(const Coords<F>& other) { return add(other); }
};

template <typename F = double>
struct Position : public Coords<F> {
  Position(int dim = default_dimension) : Coords<F>(dim)  {}
  Position(std::initializer_list<F> list) : Coords<F>(list) {} 

  virtual Position<F> operator+(const Position<F>& other) { return Coords<F>::add(other); }
};

template <typename F = double>
struct Velocity : public Coords<F> {
  Velocity(int dim = default_dimension) : Coords<F>(dim)  {}
  Velocity(std::initializer_list<F> list) : Coords<F>(list) {}  

  virtual Velocity<F> operator+(const Velocity<F>& other) { return Coords<F>::add(other); }
};

template <typename F = double>
struct Acceleration : public Coords<F> {
  Acceleration(int dim = default_dimension) : Coords<F>(dim)  {}
  Acceleration(std::initializer_list<F> list) : Coords<F>(list) {}  

  virtual Acceleration<F> operator+(const Acceleration<F>& other) { return Coords<F>::add(other); }
};

template <typename F = double, typename I = int>
struct Star {
  F mass;
  Position<F> position;

  Star(F m, Position<F> pos) : mass(m), position(pos) {}
};


// Field of points to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
template <typename F = double, typename I = int>
struct Field {
  Coords<F> c1; // negative-most bounding corner
  Coords<F> c2; // positive-most bounding corner
  std::vector<I> grid;
  std::vector<Star<F,I>> stars;
  
  I dimension;
  I cube_size;
  I iter_limit;
  
  F gravitational_constant;
  F escape_radius;
  F delta_t;
  
  Field(I cs,
        I dim,
        Coords<F> nbound,
        Coords<F> pbound) : cube_size(cs),
                            dimension(dim),
                            c1(nbound),
                            c2(pbound) {
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


} // namespace mgs
