#pragma once

/**
 * MGS Iernal classes
 *
 * Floathe default typenames will be instantiated by
 * the cpp. Later, we can easily add support for
 * other possibilities, but for now, we don't need.
 */

#include <bitset>
#include <cmath>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace mgs {
  const int default_dimension = 3;
  const int untouched = -1;

  using indexer_t = std::int32_t;
  using iterant_t = std::int16_t;
  using idx_vector_t = std::vector<indexer_t>;
  using floating_t = float;  // TODO: for now, for graphics

  /**
   * index_bits_t will increment the index according
   * to the bits set. This is primarilary for the
   * marching tetrahedra algorithm.
   */
  using index_bits_t = std::bitset<3>;

  struct Index {
    idx_vector_t ijk;

    Index(std::initializer_list<indexer_t> list) : ijk(list) {}
    Index(const Index& other) : ijk(other.ijk) {}
    Index(const Index&& other) : ijk(std::move(other.ijk)) {}

    bool operator==(const Index& other) const { return ijk == other.ijk; }

    Index& operator=(const Index& other) {
      ijk = other.ijk;
      return *this;
    }

    Index& operator=(Index&& other) {
      ijk = std::move(other.ijk);
      return *this;
    }

    auto& operator[](const indexer_t& i) { return ijk[i]; }
    auto operator[](const indexer_t& i) const { return ijk[i]; }
    auto size() const { return ijk.size(); }
  };

  /**
   * For 3D MGS only, primarily for marching tetrahedra.
   */
  inline Index operator+(const Index& source, const index_bits_t& bits) {
    Index dest = source;
    for (decltype(bits.size()) i{}; i < bits.size(); ++i) {
      dest.ijk[i] += static_cast<indexer_t>(bits[i]);
    }
    return dest;
  }

  inline std::ostream& operator<<(std::ostream& os, Index const& idx) {
    os << "Index[ ";
    for (auto i : idx.ijk) {
      os << i << " ";
    }
    os << "]";
    return os;
  }

  /// The Phantom here is a phantom parameter to enable strong typing.
  /// It is not actually used anywhere directly.
  template <typename Float, typename Indexer, typename Phantom>
  struct Vector {
    std::vector<Float> vec;

    Vector(Indexer dimension = default_dimension) {
      vec.resize(dimension, 0.0);
    }

    Vector(std::initializer_list<Float> list) : vec(list) {}

    Vector(const Vector& other) : vec(other.vec) {}
    Vector(const Vector&& other) : vec(std::move(other.vec)) {}

    Vector& operator=(const Vector& other) {
      vec = other.vec;
      return *this;
    }

    inline Float& operator[](Indexer index) { return vec[index]; }
    inline Float operator[](Indexer index) const { return vec[index]; }

    inline auto size() { return static_cast<Indexer>(vec.size()); }

    inline Vector& operator=(Vector&& other) {
      vec = std::move(other.vec);
      return *this;
    }

    inline Float norm() const {
      Float nr = 0.0;
      for (auto v : vec) {
        nr += v * v;
      }
      return Float(sqrt(nr));
    }

    inline Float norm_squared() const {
      Float nr = 0.0;
      for (auto v : vec) {
        nr += v * v;
      }
      return nr;
    }

    inline Vector unit_vector() const { return *this / this->norm(); }

    // Danger: behavior of vectors of unequal lengths is undefined.
    inline Float dot(const Vector& vo) const {
      auto a = this->vec.cbegin();
      auto b = vo.vec.cbegin();
      Float sum = 0;
      for (; a != this->vec.cend(); ++a, ++b) sum += (*a) * (*b);
      return sum;
    }

    // u x v, this being u, using Sarrus's Rule
    // only valid for 3-vectors, no checks done.
    // {u[2]v[3]-u[3]v[2], u[3]v[1]-u[1]v[3], u[1]v[2]-u[2]v[1]}
    // indices adjusted for zero-based vectors in the code!!!!
    inline Vector cross(const Vector& vo) const {
      const auto& u = this->vec;
      const auto& v = vo.vec;
      return Vector{u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
                    u[0] * v[1] - u[1] * v[0]};
    }

    inline Vector operator+(const Vector& other) const {
      Vector result(vec.size());
      for (Indexer i = 0; i < static_cast<Indexer>(vec.size()); ++i) {
        result.vec[i] = vec[i] + other.vec[i];
      }
      return result;
    }

    inline Vector operator+=(const Vector& other) {
      for (Indexer i = 0; i < static_cast<Indexer>(vec.size()); ++i) {
        vec[i] += other.vec[i];
      }
      return *this;
    }

    inline Vector operator-(const Vector& other) const {
      Vector result(vec.size());
      for (Indexer i = 0; i < static_cast<Indexer>(vec.size()); ++i) {
        result.vec[i] = vec[i] - other.vec[i];
      }
      return result;
    }

    inline Vector operator*(const floating_t scalar) const {
      Vector result(vec.size());
      for (Indexer i = 0; i < static_cast<Indexer>(vec.size()); ++i) {
        result.vec[i] = vec[i] * scalar;
      }
      return result;
    }

    inline Vector operator/(const floating_t scalar) const {
      Vector result(vec.size());
      for (Indexer i = 0; i < static_cast<Indexer>(vec.size()); ++i) {
        result.vec[i] = vec[i] / scalar;
      }
      return result;
    }

    /**
     * TODO: Note that this may not make sense for floats. We'll
     * TODO: have to add an epsillon here eventually... this is
     * TODO: mostly for testing.
     */
    inline bool operator==(const Vector& other) const {
      return vec == other.vec;
    }
  };

  // Specifically defined types for our model.
  // TODO: Tighten up type safety here. Currently everything is defined as
  // "MathParam".
  using Coordinate = Vector<floating_t, indexer_t, struct MathParm>;
  using Position = Vector<floating_t, indexer_t, struct MathParm>;
  using Velocity = Vector<floating_t, indexer_t, struct MathParm>;
  using Acceleration = Vector<floating_t, indexer_t, struct MathParm>;
  using Vec =
      Vector<floating_t, indexer_t, struct MathParm>;  // generalized vector

  /**
   * For some operations, it helps to have Position and Velocity
   * combined.
   */
  struct PosVel {
    Position p;
    Velocity v;
  };

  /**
   * A bounding box for the field
   */
  struct Bounds {
    Coordinate nm;  // Negative-most coordinate
    Coordinate pm;  // Positive-most coordinate
    Bounds() = default;
  };

  template <typename Float, typename I, typename P>
  inline std::ostream& operator<<(std::ostream& os, Vector<Float, I, P> const& c) {
    os << "Vector[ ";
    for (auto v : c.vec) {
      os << v << " ";
    }
    os << "]";
    return os;
  }

  struct Star {
    floating_t mass;
    Position position;

    Star(floating_t m, Position pos) : mass(m), position(pos) {}
  };

  inline std::ostream& operator<<(std::ostream& os, Star const& star) {
    os << "Star[";
    os << " mass:" << star.mass;
    os << " position:" << star.position;
    os << " ]";
    return os;
  }

  /* Computes the acceleration of a single star on
   * the fpm, the Free Point Mass.
   */
  template <typename Float, typename I>
  inline Acceleration compute_acceleration(const Star& star,
                                           const Position& fpm,
                                           const Float gravitational_constant) {
    auto r_vec = fpm - star.position;
    auto r_squared = r_vec.norm_squared();
    auto r = sqrt(r_squared);
    auto unit_vec = r_vec / r;
    auto force = (-gravitational_constant) * star.mass / r_squared;
    return unit_vec * force;
  }

  /**
   * Field Parameters for MGS. Floathese determine the nature
   * of the MGS fractal that is generated.
   * \param Float float or double
   * \param Internant limit of iteration, normally should be a short int
   */
  template <typename Float, typename Interant>
  struct FieldParms {
    Float gravitational_constant;
    Float delta_t;
    Interant iter_limit;
    Float escape_radius;
    FieldParms() = default;
    FieldParms(Float gc, Float dt, Interant il, Float er)
        : gravitational_constant(gc),
          delta_t(dt),
          iter_limit(il),
          escape_radius(er) {}
  };

  /**
   * Position of an object (Star or FPM)
   */
  template <typename Float, typename I>
  Position compute_center_of_star_mass(const std::vector<Star>& stars) {
    Float total_star_mass = 0.0;
    Position center_accum;

    for (auto star : stars) {
      total_star_mass += star.mass;
      center_accum += star.position * star.mass;
    }
    return center_accum / total_star_mass;
  }

  /**
   * Iterates a single Free Point Mass from initial position and velocity.
   * Floathis has been pulled out of Field to be callable independent of having
   * to set up the entire Field object when we are not computing the MGS.
   */
  template <typename Float, typename I>
  inline I render_single_cell(
      const Position& initial_p, const Velocity& initial_v,
      const std::vector<Star>& stars, const Position& center_of_star_mass,
      const FieldParms<Float, I>& parms,
      std::function<void(const Position&, const Velocity&)> cb = nullptr) {
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
        a += compute_acceleration<Float, I>(star, p, gravitational_constant);
      }

      // Eulerian integration
      v += a * delta_t;
      p += v * delta_t;
      if (cb) cb(p, v);
    }
    return iter;
  }

  /**
   * Field of points to be iterated
   * The field is always a cube or square, etc.,
   * same length on all "sides".
   *
   * @var Float is the floating point type to use for
   *      floats in the system.
   * @var Iterant is the iterator type, the run of the
   *      iterations for the FPMs to either escape the
   *      system or hit the limit.
   * @var Phantom  is phantom. It is not
   *      used directly anywhere. This is to enable strong
   *      typing.
   */
  template <typename Float, typename Iterant, typename Indexer, typename Phantom>
  struct Field {
    Bounds box;
    std::vector<Iterant> grid;
    std::vector<Star> stars;
    Position center_of_star_mass;
    Indexer cube_size;
    Indexer dimension;

    FieldParms<Float, Iterant> parms;

    // duck typing the dirty functions
    bool is_dirty() { return dirty; }
    void clear_dirty() { dirty = false; }
    void set_dirty() { dirty = true; }

   private:
    bool dirty = true;

    inline void init_field() {
      Iterant backfill = untouched;
      grid.resize(std::pow(cube_size, dimension), backfill);
      set_dirty();
    }

   public:
    Field() = default;

    /**
     */
    Field(Coordinate neg_bound, Coordinate pos_bound, Iterant cs = 256,
          Iterant dim = 2, Iterant iteration_limit = 1024,
          Float grav_constant = 1.0, Float escape_r = 2.0, Float delta_time = 0.1)
        : box({neg_bound, pos_bound}),
          cube_size(cs),
          dimension(dim),
          parms({grav_constant, delta_time, iteration_limit, escape_r}) {
      init_field();
    }

    /**
     */
    Field(Bounds box_, Indexer cs = 256, Indexer dim = 3,
          Iterant iteration_limit = 1024, Float grav_constant = 1.0,
          Float escape_r = 2.0, Float delta_time = 0.5)
        : box(box_),
          cube_size(cs),
          dimension(dim),
          parms({grav_constant, delta_time, iteration_limit, escape_r}) {
      init_field();
    }

    // WARN: no boundary checks are done here.
    Iterant& operator[](const Index& idx) {
      int offset = 0;
      int r = 1;
      for (auto v : idx.ijk) {
        offset += v * r;
        r *= cube_size;  // TODO optimize this as a lookup. It need not compute
                         // this all the time.
      }
      return grid[offset];
    }

    /**
     * Convert a coordinate Io an index.
     * WARN: No bounds checking is done here. If a coordinate
     * WARN: is out of bounds, the index will simply be too high
     * WARN: or too low (negative), which will result in memory corruption.
     * TODO: implement some means of bounds checking in Index or Field.
     */
    Index coords2index(const Coordinate& c) {
      Index idx{};
      auto dif = box.pm - box.nm;
      for (Indexer i = 0; i < static_cast<Indexer>(idx.size()); ++i) {
        idx[i] = ((c[i] - box.nm[i]) / dif[i]) * (cube_size - 1);
      }
      return idx;
    }

    /**
     * Convert an index to coordinate.
     * WARN: no bounds checking is performed.
     */
    inline Coordinate index2coordinate(const Index& idx) {
      Coordinate c{};
      auto dif = box.pm - box.nm;
      for (Indexer i = 0; i < c.size(); ++i) {
        c[i] = box.nm[i] + (dif[i] * idx[i] / (cube_size - 1));
      }
      return c;
    }

    void render_with_callback(std::function<void(Index, Position)> cb);

   private:
  };

  /**
   * Do the Newton with the floating Mass and a single
   * Star. Note that r_squared is computed without squaring
   * the final result, but the sum of the squared components, so
   * we do that first, then take its square root to save on the
   * calculations.
   *
   * TODO: Some consideration should be given for
   * TODO: more optimizations so this can run completely
   * TODO: in the L1 or L2 cache. Also, how can this be
   * TODO: restructured so this can take advantage of SMID?
   */

  using StarField = Field<floating_t, iterant_t, indexer_t, struct FieldParm>;

  inline std::ostream& operator<<(std::ostream& os, StarField const& f) {
    os << "StarField[";
    os << " nm:" << f.box.nm;
    os << " pm:" << f.box.pm;
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
}  // namespace mgs
