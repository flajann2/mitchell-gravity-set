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

  using tetra_index = std::array<unsigned char, 4>;
  using cube_decomposer = std::array<tetra_index, 6>;

  static const cube_decomposer dicer{{{0, 1, 3, 7},
                                      {0, 2, 3, 7},
                                      {0, 2, 6, 7},
                                      {0, 4, 6, 7},
                                      {0, 4, 5, 7},
                                      {0, 1, 5, 7}}};

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

   public:
    MakeTesselation(const StarField& field) : m_field(field) {}
    MakeTesselation(const StarField&& field) : m_field(std::move(field)) {}

    /**
     * From the lower most point index, testelate
     * the cube to the upper most point (basically by adding 1
     * to the indices of the lmp).
     */
    void tesseltate_cube(const Index& lmp);

    template <typename Shape>
    Shape operator()() {}
  };
}  // namespace mgs::march
