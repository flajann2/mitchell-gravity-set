#include <memory>
#include <iostream>
#include <compute.h>

using namespace std;

namespace mgs {
  extern "C++" {
    
    template <typename T, typename I, typename P>
    void Field<T,I,P>::render_with_callback(std::function<void(Index, Position)> cb) {
      center_of_star_mass = compute_center_of_star_mass<T,I>(stars);
    }
    
    
    // so that StarField is instantiated in this library.
    // FIXME: This is a duplication of StarField.
    template struct Field<double, int, struct FieldParm>;
  }
}
