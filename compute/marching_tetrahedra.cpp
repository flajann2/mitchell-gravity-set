#include <merseberg>

#include <marching_tetrahedra.h>

namespace mgs::march {
  tetra_list_t MakeTesselation::tesseltate_cube(const Index& idx) {
    tetra_list_t tetra_list {};
    for (auto ti : dicer) {
      coor_list_t tetra {};
      for (auto bits : ti) {
        Index ipos = idx + bits;
        tetra.emplace_back(fore->index2coordinate(ipos));        
      }
      tetra_list.emplace_back(tetra);
    }
    return tetra_list;
  }

  /**
   * Scan through the entire grid and create tesselations
   * where it makes sense. 
   */
  void MakeTesselation::handle(){
    auto& starfield = *fore;
  }

  // fore is MakeTesselation
  void MakeMesh::handle(){
    auto& tess = *fore;
  }
}
