#pragma once

#include "compute.h"

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
  static_assert(sizeof(gpu_coordinate_t{0,0,0})*2 == sizeof(mesh_vertices_t{{0},{0}}), "Mesh triangle vertices are not aligned for this architecture.");
  static_assert(sizeof(mesh_triangle_indices_t)*2 == sizeof(mesh_triangle_indices_list_t{{1,2,3},{4,5,6}}), "Mesh Triangle indicies are not aligned for this architecture.");
  
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
   */
  class Pipeline {};

  /**
   * We create the initial list of polygons here (not
   * necessarily in the form needed for OpenGL!!!)
   */
  class MakeTesselation : public Pipeline {
    StarField m_field;
    friend std::ostream& operator<<(std::ostream&, MakeTesselation const&);

   public:
    MakeTesselation() = default;
    MakeTesselation(const StarField& field) : m_field(field) {}
    MakeTesselation(const StarField&& field) : m_field(std::move(field)) {}

    /**
     * From the lower most point index, testelate
     * the cube to the upper most point (basically by adding 1
     * to the indices of the lmp).
     */
    tetra_list_t tesseltate_cube(const Index& lmp);

    template <typename Shape>
    Shape operator()() {}
  };

  inline std::ostream& operator<<(std::ostream& os,
                                  MakeTesselation const& tess) {
    os << "MakeTesselation [\n";
    os << tess.m_field << "\n]\n";
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
  class MakeMesh : public Pipeline {
    const MakeTesselation& m_tess;
  public:
    MakeMesh() = default;
    MakeMesh(const MakeTesselation& tess) : m_tess(tess) {}
  };
}  // namespace mgs::march
