#include <marching_tetrahedra.h>

namespace mgs::march {
  pos_list_t MakeTesselation::tesseltate_cube(const Index& idx) {
    pos_list_t tetra {};
    for (auto ti : dicer) {
      for (auto bits : ti) {
        Index ipos = idx + bits;
        tetra.emplace_back(m_field.index2coordinate(ipos));        
      }
    }
    return tetra;
  }

}
