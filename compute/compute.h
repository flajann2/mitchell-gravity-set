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
  const int default_dimension = 3;
  const int untouched = -1;
  
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
  
  inline std::ostream &operator<<(std::ostream &os, Index const &idx) {
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


    inline T& operator[](I index)  {
      return vec[index];
    }

    inline Vector& operator=(Vector&& other)  {
      vec = std::move(other.vec);
      return *this;
    }
    

    T norm() {
      T nr = 0.0;
      for (auto v : vec) { nr += v * v; }
      return T (sqrt(nr));
    }
  
    T norm_squared() {
      T nr = 0.0;
      for (auto v : vec) { nr += v * v; }
      return nr;
    }
      
    Vector unit_vector() {
      return *this / this->norm();
    }
    
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
  using Coordinate   = Vector<double, int, struct CoordinateParm>;
  using Position     = Vector<double, int, struct MathParm>;
  using Velocity     = Vector<double, int, struct MathParm>;
  using Acceleration = Vector<double, int, struct MathParm>;

  // For some operations, it helps to have Position and Velocity
  // combined.
  struct PosVel {
    Position p;
    Velocity v;
  };

  template <typename T, typename I, typename P>
  inline std::ostream &operator<<(std::ostream &os, Vector<T, I, P>const &c) {
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
  
  inline std::ostream &operator<<(std::ostream &os, Star const &star) {
    os << "Star[";
    os << " mass:" << star.mass;
    os << " position:" << star.position;
    os << " ]";
    return os;
  }

  /* Computes the acceleration of a single star on
   * the fpm, the Free Point Mass.
   */
  template <typename T, typename I>
  inline Acceleration compute_acceleration(const Star& star,
                                           const Position& fpm,
                                           const T gravitational_constant) {
    auto r_vec = fpm - star.position;
    auto r_squared = r_vec.norm_squared();
    auto r = sqrt(r_squared);
    auto unit_vec = r_vec / r;
    auto force = (-gravitational_constant) * star.mass / r_squared;
    return unit_vec * force;
  }


  template <typename T, typename I>
  struct FieldParms {
    T gravitational_constant;
    T delta_t;
    I iter_limit;
    T escape_radius;
    FieldParms() = default;
    FieldParms(T gc, T dt, I il, T er) : gravitational_constant(gc),
                                         delta_t(dt),
                                         iter_limit(il),
                                         escape_radius(er) {}
  };

  template <typename T, typename I>
  Position compute_center_of_star_mass(const std::vector<Star>& stars) {
    T total_star_mass = 0.0;
    Position center_accum;
    
    for (auto star : stars) {
      total_star_mass += star.mass;
      center_accum += star.position * star.mass;
    }
    return center_accum / total_star_mass;
  }
  
  /* Iterates a single Free Point Mass from initial position and velocity.
   * This has been pulled out of Field to be callable independent of having
   * to set up the entire Field object when we are not computing the MGS.
   */
  template <typename T, typename I>
  inline I render_single_cell(const Position& initial_p,
                              const Velocity& initial_v,
                              const std::vector<Star>& stars,
                              const Position& center_of_star_mass,
                              const FieldParms<T,I>& parms,
                              std::function<void(const Position&,
                                                 const Velocity&)> cb = nullptr) {
    auto [gravitational_constant, delta_t, iter_limit, escape_radius] = parms;
    auto v = initial_v;
    auto p = initial_p;
    I iter = 0;
    
    for (iter = 0;
         iter < iter_limit && (p - center_of_star_mass).norm() <= escape_radius;
         ++iter) {
      
      Acceleration a;
      
      // acceleration due to all the stars
      for (auto star : stars) {
        a += compute_acceleration<T,I>(star, p, gravitational_constant);
      }
      
      // Eulerian integration
      v += a * delta_t;
      p += v * delta_t;
      if (cb) cb(p, v);
    }
    return iter;
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

    FieldParms<T,I> parms;
     
    Field(Coordinate nbound,
          Coordinate pbound,          
          I cs = 1024,
          I dim = 2,
          I iteration_limit = 1024,
          T grav_constant = 1.0,
          T escape_r = 2.0,
          T delta_time = 0.1) : c1(nbound),
                                c2(pbound),
                                cube_size(cs),
                                dimension(dim),
                                parms({grav_constant, delta_time, iteration_limit, escape_r}) {
      I backfill = untouched;
      grid.resize(std::pow(cs, dim), backfill);
    }
    
    // WARN: no boundary checks are done here.
    I& operator[](Index& idx) {
      int offset = 0;
      int r = 1;
      for (auto v : idx.ijk) {
        offset += v * r;
        r *= cube_size;
      }
      return grid[offset];
    }

    
    // Convert a coordinate Io an index.
    // WARN: No bounds checking is done here.
    Index coords2index(Coordinate& c) {
      // TODO: Implement 
      return Index{};
    }

    void render_with_callback(std::function<void(Index, Position)> cb);
    
  private:
  };

  /*
   * Do the Newton with the Floating Point16_t Mass and a single
   * Star. Note that r_squared is computed without squaring
   * the final result, but the sum of the squared components, so
   * we do that first, then take it's square root to save on the
   * calculations.
   *
   * TODO: Some consideration should be given for
   * TODO: more optimizations so this can run completely
   * TODO: in the L1 or L2 cache. Also, how can this be
   * TODO: restructured so this can take advantage of SMID?
   */

  using StarField = Field<double, int, struct FieldParm>;

  inline std::ostream &operator<<(std::ostream &os, StarField const &f) {
    os << "StarField[";
    os << " c1:" << f.c1;
    os << " c2:" << f.c2;
    os << " cube_size:" << f.cube_size;
    os << " dimension:" << f.dimension;
    os << " iter_limit:" << f.parms.iter_limit;
    os << " gravitational_constant:" << f.parms.gravitational_constant;
    os << " escappe_radius:" << f.parms.escape_radius;
    os << " delta_t:" << f.parms.delta_t;
    
    os << "Stars[ ";
    for (auto star : f.stars) {
      os << star << " ";
    }
    os << "]";
    
    os << "]"; 
    return os;
  }
} // namespace mgs::compute
