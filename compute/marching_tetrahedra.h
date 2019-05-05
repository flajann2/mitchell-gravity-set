#pragma once

#include "compute.h"
#include <mutex>

/**
 * The Marching Tetrahedra is implemented here.
 * We simply wish (for now) to walk the entire field
 * and generate the triangles to render.
 *
 * TODO: later on we will optimise this to
 * TODO: process in a more lazy fashion. For now,
 * TODO: we will generate a "buffer" of polygons
 * TODO: that will eventually be rendered.
 */

namespace mgs::march {
  using namespace mgs;

  /// A zero here means to let Merseberg decide how many
  /// workers to create.
  constexpr std::size_t imp_workers = 1; // TODO: fix currency problem

  using tetra_index_t = std::array<index_bits_t, 4>;
  using cube_decomposer_t = std::array<tetra_index_t, 6>;
  using coor_list_t = std::vector<Coordinate>;
  using tetra_list_t = std::vector<coor_list_t>;
  using gpu_coordinate_t = std::array<floating_t, 3>;
  using mesh_vertices_t = std::vector<gpu_coordinate_t>;
  using indexer_gpu_t = std::int32_t;
  using mesh_triangle_indices_t = std::array<indexer_gpu_t, 3>;
  using mesh_triangle_indices_list_t = std::vector<mesh_triangle_indices_t>;

  // Sanity checks for alignment
  static_assert(
      sizeof(gpu_coordinate_t{0, 0, 0}) * 2 ==
          sizeof(mesh_vertices_t{{0}, {0}}),
      "Mesh triangle vertices are not aligned for this architecture.");
  static_assert(
      sizeof(mesh_triangle_indices_t) * 2 ==
          sizeof(mesh_triangle_indices_list_t{{1, 2, 3}, {4, 5, 6}}),
      "Mesh Triangle indicies are not aligned for this architecture.");

  inline std::ostream& operator<<(std::ostream& os, coor_list_t const& pv) {
    os << "pos_list[" << '\n';
    for (auto p : pv) {
      os << "   " << p << '\n';
    }
    os << "]\n";
    return os;
  }

  /**
   * The cube decomposer describes how to slice a cube into the 6
   * tetrahedra. The encoding is such that the vertex of the cube
   * is determined by adding a zero or one to each of the
   * lower most position's elements. To emphasis this, we represent
   * the offets by binary.
   */
  static const cube_decomposer_t dicer{{{0b000, 0b001, 0b011, 0b111},
                                        {0b000, 0b010, 0b011, 0b111},
                                        {0b000, 0b010, 0b110, 0b111},
                                        {0b000, 0b100, 0b110, 0b111},
                                        {0b000, 0b100, 0b101, 0b111},
                                        {0b000, 0b001, 0b101, 0b111}}};

  /**
   * Production is done in a pipeline fashion,
   * and later will be made lazy. All classes
   * involved in the pipeline shall be derived
   * from this one.
   *
   * \THIS -- current class (CRTP)
   * \FORE -- THIS << FORE relationship
   */
  template <typename THIS, typename FORE>
  class Pipeline {
   protected:
    FORE* fore = nullptr;
    bool dirty = true;
    std::mutex p_mutex;

   public:
    bool is_dirty() {
      return dirty || (fore != nullptr ? fore->is_dirty() : false);
    }
    void set_dirty() { dirty = true; }
    void clear_dirty() {
      dirty = false;
      if (fore != nullptr) {
        fore->clear_dirty();
      }
    }

    /**
     * General pipeline operator between THIS and FORE.
     */
    THIS& operator<<=(FORE& fore_) {
      fore = &fore_;
      THIS& that = static_cast<THIS&>(*this);
      that.handle();  // static duck typing
      return that;
    }
  };

  /**
   * We create the list of tetraherea here
   */
  class MakeTesselation : public Pipeline<MakeTesselation, StarField> {
    friend std::ostream& operator<<(std::ostream&, MakeTesselation const&);

    tetra_list_t m_tetrahedra;

   public:
    MakeTesselation() {};

    /**
     * handle() generates the list of tetrahedra. Note that
     * only tetrahedra that intersects with the crossover are
     * retained; the rest are discarded.
     */
    void handle();

    /**
     * From the lower most point index, testelate
     * the cube to the upper most point (basically by adding 1
     * to the indices of the lmp).
     *
     * Note that this function does not automatically add the result
     * to m_tetrahedra. That must be done by the caller.
     */
    tetra_list_t tesselate_cube(const Index& lmp) const;
  };

  inline std::ostream& operator<<(std::ostream& os,
                                  MakeTesselation const& tess) {
    os << "MakeTesselation [\n";
    os << tess.fore << "\n]\n";
    return os;
  }

  inline std::ostream& operator<<(std::ostream& os, tetra_list_t const& tl) {
    os << "tetra_list: [ \n";
    for (auto t : tl) {
      os << "  " << t << '\n';
    }
    os << "]";

    return os;
  }

  /**
   * We take the results from MakeTesselation to now make the mesh.
   */
  class MakeMesh : public Pipeline<MakeMesh, MakeTesselation> {
   public:
    MakeMesh() {}

    void handle();  // duck typing
  };
}  // namespace mgs::march

namespace std {
  template <class T, class Alloc>
  void operator+=(std::vector<T, Alloc>& lhs,
                  const std::vector<T, Alloc>& rhs) {
    for (auto ele : rhs) {
      lhs.push_back(ele);
    }
  }
}
