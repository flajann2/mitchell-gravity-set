#pragma once

/*
 * MGS Iernal classes
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

  // The P here is a phantom parameter to enable strong typing.
  // It is not actually used anywhere directly.
  template <typename T, typename I, typename P>
  struct Vector {
    std::vector<T> vec;
    
    Vector(I dimension = default_dimension) { vec.resize(dimension, 0.0); }
    Vector(std::initializer_list<T> list) : vec(list) {}
    
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
    
    inline T norm();
    inline T norm_squared();
    inline Vector unit_vector();
    
    inline Vector operator+(const Vector& other) const {
      Vector result(vec.size());
      for (unsigned i = 0; i < vec.size(); ++i) { result.vec[i] = vec[i] + other.vec[i]; }
      return result;
    }
    
    inline Vector operator+=(const Vector& other) {
      for (unsigned i = 0; i < vec.size(); ++i) { vec[i] += other.vec[i]; }
      return *this;
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

  // Specifically defined types for our model.
  using Coordinate   = Vector<double, std::int16_t, struct CoordinateParm>;
  using Position     = Vector<double, std::int16_t, struct MathParm>;
  using Velocity     = Vector<double, std::int16_t, struct MathParm>;
  using Acceleration = Vector<double, std::int16_t, struct MathParm>;

  template <typename T, typename I, typename P>
  std::ostream &operator<<(std::ostream &os, Vector<T, I, P>const &c) {
    os << "Vector[ ";
    for (auto v : c.vec) { os << v << " ";  }
    os << "]";
    return os;
  }
  
  struct Star {
    double mass;
    Position position;
    
    Star(double m, Position pos) : mass(m), position(pos) {}
  };
  
  std::ostream &operator<<(std::ostream &os, Star const &star) {
    os << "Star[";
    os << " mass:" << star.mass;
    os << " position:" << star.position;
    os << " ]";
    return os;
  }
  
  /* Field of poIs to be iterated
   * The field is always a cube or square, etc.,
   * same length on all "sides".
   *  
   * Also, the P parameter is phantom. It is not
   * used directly anywhere. This is to enable strong
   * typing.
   */
  template <typename T, typename I, typename P>
  struct Field {
    Coordinate c1; // negative-most bounding corner
    Coordinate c2; // positive-most bounding corner
    
    std::vector<I> grid; // TODO: Can we get away with int8 here?
    std::vector<Star> stars;
    
    Position center_of_star_mass;
    
    I cube_size;
    I dimension;
    I iter_limit;
    
    double gravitational_constant;
    double escape_radius;
    double delta_t;
    
    Field(Coordinate nbound,
          Coordinate pbound,          
          I cs = 1024,
          I dim = 2,
          I iteration_limit = 1024,
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
      I backfill = untouched;
      grid.resize(std::pow(cs, dim), backfill);
    }
    
    // WARN: no boundary checks are done here.
    I& operator[](Index& idx); 
    
    // Convert a coordinate Io an index.
    // WARN: No bounds checking is done here.
    Index coords2index(Coordinate& c);
    void render_with_callback(std::function<void(Index, Position)> cb);
    Position compute_center_of_star_mass();
    
  private:
    I render_single_cell(const Position& initial_p,
                         const Velocity& initial_v);
    inline Acceleration compute_acceleration(const Star& star, const Position& fpm) const;
  };
  using StarField = Field<double, std::int16_t, struct FieldParm>;

  std::ostream &operator<<(std::ostream &os, StarField const &f) {
    os << "StarField[";
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
} // namespace mgs::compute
