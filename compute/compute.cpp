import std;

using namespace std;

namespace mgs {
  extern "C++" {
    
    template <typename T, typename Interant, typename Indexer, typename P>
    void Field<T,Interant,Indexer,P>::render_with_callback(std::function<void(Index, Position)> cb) {
      center_of_star_mass = compute_center_of_star_mass<T,Indexer>(stars);
    }
    
    
    // so that StarField is instantiated in this library.
    // FIXME: This is a duplication of StarField.
    template struct Field<floating_t, iterant_t, indexer_t, struct FieldParm>;
  }
}
