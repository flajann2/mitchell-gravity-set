/*
 * MGS std::int16_ternal classes
 *
 * The default typenames will be instantiated by
 * the cpp. Later, we can easily add support for
 * other possibilities, but for now, we don't need.
 */

#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstdint>
#include <functional>
#include <utility>

namespace mgs {

const std::int16_t default_dimension = 2;
const std::int16_t untouched = -1;

struct Index {
  std::vector<std::int32_t> ijk;
  
  Index(std::initializer_list<std::int32_t> list) : ijk(list) {}
  Index(const Index& other)  : ijk(other.ijk) {}
  Index(const Index&& other) : ijk(std::move(other.ijk)) {}
  
  Index& operator=(const Index& other) {
    ijk = other.ijk;
    return *this;
  }
  
  Index& operator=(Index&& other)  {
    ijk = std::move(other.ijk);
    return *this;
  }
};

std::ostream &operator<<(std::ostream &os, Index const &idx) {
  os << "Index[ ";
  for (auto i : idx.ijk) { os << i << " "; }
  os << "]";
  return os;
}

struct Vector {
  std::vector<double> vec;
  
  Vector(std::int16_t dimension = default_dimension) { vec.resize(dimension, 0.0); }
  Vector(std::initializer_list<double> list) : vec(list) {}

  Vector(const Vector& other) : vec(other.vec) {}
  Vector(const Vector&& other) : vec(std::move(other.vec)) {}

  Vector& operator=(const Vector& other) {
    vec = other.vec;
    return *this;
  }
  
  Vector& operator=(Vector&& other)  {
    vec = std::move(other.vec);
    return *this;
  }
  
  inline double norm();
  inline double norm_squared();
  inline Vector unit_vector();

  inline Vector operator+(const Vector& other) const {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] + other.vec[i]; }
    return result;
  }
  
  inline Vector operator-(const Vector& other) const {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] - other.vec[i]; }
    return result;
  }
  
  inline Vector operator*(const double scalar) const {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] * scalar; }
    return result;
  }
  
  inline Vector operator/(const double scalar) const {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] / scalar; }
    return result;
  }
};

std::ostream &operator<<(std::ostream &os, Vector const &c) {
  os << "Vector[ ";
  for (auto v : c.vec) { os << v << " ";  }
  os << "]";
  return os;
}

struct Star {
  double mass;
  Vector position;

  Star(double m, Vector pos) : mass(m), position(pos) {}
};

std::ostream &operator<<(std::ostream &os, Star const &star) {
  os << "Star[";
  os << " mass:" << star.mass;
  os << " position:" << star.position;
  os << " ]";
  return os;
}

// Field of postd::int16_ts to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
struct Field {
  Vector c1; // negative-most bounding corner
  Vector c2; // positive-most bounding corner

  std::vector<std::int16_t> grid; // TODO: Can we get away with int8 here?
  std::vector<Star> stars;
  
  std::int16_t cube_size;
  std::int16_t dimension;
  std::int16_t iter_limit;
  
  double gravitational_constant;
  double escape_radius;
  double delta_t;
  
  Field(Vector nbound,
        Vector pbound,

        std::int16_t cs = 1024,
        std::int16_t dim = 2,
        std::int16_t iteration_limit = 1024,
        double grav_constant = 1.0,
        double escape_r = 2.0,
        double delta_time = 0.1) : c1(nbound),
                                   c2(pbound),
                                   cube_size(cs),
                                   dimension(dim),
                                   iter_limit(iteration_limit),
                                   gravitational_constant(grav_constant),
                                   escape_radius(escape_r),
                                   delta_t(delta_time) {
    std::int16_t backfill = untouched;
    grid.resize(std::pow(cs, dim), backfill);
  }

  // WARN: no boundary checks are done here.
  std::int16_t& operator[](Index& idx); 

  // Convert a coordinate std::int16_to an index.
  // WARN: No bounds checking is done here.
  Index coords2index(Vector& c);
  void render_with_callback(std::function<void(Index, Vector)> cb);

 private:
  std::int16_t render_single_cell(const Vector& initial_p, const Vector& initial_v);
  inline Vector compute_acceleration(const Star& star, const Vector& fpm) const;
};

std::ostream &operator<<(std::ostream &os, Field const &f) {
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
