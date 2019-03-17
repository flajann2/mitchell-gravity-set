#include <marching_tetrahedra.h>

namespace mgs::march {
  tetra_list_t MakeTesselation::tesseltate_cube(const Index& idx) {
    tetra_list_t tetra_list {};
    for (auto ti : dicer) {
      pos_list_t tetra {};
      for (auto bits : ti) {
        Index ipos = idx + bits;
        tetra.emplace_back(m_field.index2coordinate(ipos));        
      }
      tetra_list.emplace_back(tetra);
    }
    return tetra_list;
  }
}
