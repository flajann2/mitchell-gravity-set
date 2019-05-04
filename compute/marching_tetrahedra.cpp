#include <marching_tetrahedra.h>
#include <format> // for the future
#include <merseberg>
#include <mutex>

using namespace std;
namespace mgs::march {
  /**
   * Tesselate cube into 6 tetrahedra.
   * @param lmc -- lower most corner of cube
   */
  tetra_list_t MakeTesselation::tesselate_cube(const Index& lmc) {
    tetra_list_t tetra_list{};
    for (auto ti : dicer) {
      coor_list_t tetra{};
      for (auto bits : ti) {
        Index ipos = lmc + bits;
        tetra.emplace_back(std::move(fore->index2coordinate(ipos)));
      }
      tetra_list.emplace_back(tetra);
    }
    return tetra_list;
  }

  /**
   * Scan through the entire grid and create tesselations
   * where it makes sense.
   *
   * Here, we create a collection of i indices to spit
   * across worker threads, and each worker will iterate
   * through the j & k'indices.
   */
  void MakeTesselation::handle() {
    auto& starfield = *fore;
    std::vector<indexer_t> vi{};
    for (indexer_t i = 0; i < starfield.cube_size - 1; ++i) {
      vi.push_back(i);
    }

    auto imp = merseberg::incantation(vi);
    auto worker = [&](auto begin, auto end) {
      tetra_list_t tetra {};
      for (auto pi = begin; pi != end; ++pi) {
        auto& i = *pi;
        for (auto j = 0; j < starfield.cube_size - 1; ++j) {
          for (auto k = 0; k < starfield.cube_size - 1; ++k) {
            Index lmc{i, j, k};              // lower-most corner of cube.
            tetra += tesselate_cube(lmc);            
          }
        }
      }
      
      std::scoped_lock(p_mutex);
      m_tetrahedra += tetra;
      return 0;
    };
    imp.invoke(worker);
    imp.join();
  }

  // fore is MakeTesselation
  void MakeMesh::handle() { auto& tess = *fore; }
}  // namespace mgs::march
