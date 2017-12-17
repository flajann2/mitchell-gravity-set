/*
 * MGS internal classes
 */

#include <vector>
#include <initializer_list>

using namespace std;

const int default_dimension= 2;

template <class T = double> struct Scalar {
  T value;
  explicit Scalar(T v) : value(v) {}
};

template <class T = double> struct Coords {
  vector<T> vec;
  
  Coords(int dim = default_dimension) { vec.resize(dim); }
  Coords(initializer_list<T> list) : vec(list) {}
};
  
template <class T = double> struct Position : public Coords<T> {
  Position(int dim = default_dimension) : Coords<T>(dim)  {}
  Position(initializer_list<T> list) : Coords<T>(list) {}  
};
  
template <class T = double> struct Velocity : public Coords<T> {
  Velocity(int dim = default_dimension) : Coords<T>(dim)  {}
  Velocity(initializer_list<T> list) : Coords<T>(list) {}  
};

template <class T = double> struct Acceleration : public Coords<T> {
  Acceleration(int dim = default_dimension) : Coords<T>(dim)  {}
  Acceleration(initializer_list<T> list) : Coords<T>(list) {}  
};

  template <class T> class Space {
};
