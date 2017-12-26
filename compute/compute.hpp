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

struct Index {
  std::vector<int> ijk;
  Index(std::initializer_list<int> list) : ijk(list) {}
};

std::ostream &operator<<(std::ostream &os, Index const &idx) {
  os << "Index[ ";
  for (auto i : idx.ijk) { os << i << " "; }
  os << "]";
  return os;
}

struct Vector {
  std::vector<double> vec;
  
  Vector(int dimension = default_dimension) { vec.resize(dimension, 0.0); }
  Vector(std::initializer_list<double> list) : vec(list) {}
 
  double norm();
  double norm_squared();
  Vector unit_vector();

  virtual Vector operator+(const Vector& other) {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] + other.vec[i]; }
    return result;
  }
  
  virtual Vector operator-(const Vector& other) {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] - other.vec[i]; }
    return result;
  }
  
  virtual Vector operator*(const double scalar) {
    Vector result(vec.size());
    for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] * scalar; }
    return result;
  }
  
  virtual Vector operator/(const double scalar) {
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

// Field of points to be iterated
// The field is always a cube or square, etc.,
// same length on all "sides".
struct Field {
  Vector c1; // negative-most bounding corner
  Vector c2; // positive-most bounding corner

  std::vector<int> grid;
  std::vector<Star> stars;
  
  int cube_size;
  int dimension;
  int iter_limit;
  
  double gravitational_constant;
  double escape_radius;
  double delta_t;
  
  Field(Vector nbound,
        Vector pbound,

        int cs = 1024,
        int dim = 2,
        int iteration_limit = 1024,
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
    int backfill = untouched;
    grid.resize(std::pow(cs, dim), backfill);
  }

  // WARN: no boundary checks are done here.
  int& operator[](Index& idx); 

  // Convert a coordinate into an index.
  // WARN: No bounds checking is done here.
  Index coords2index(Vector& c);
  void render_with_callback(std::function<void(Index, Vector)> cb);

 private:
  int render_single_cell(Vector initial_p, Vector initial_v);
  double compute_newton_g(const Star& star, const Vector& fpm);
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
