/*
 * MGS internal classes
 */
#include <vector>
using namespace std;

template <class T> struct Scalar {
  T value;
  explicit Scalar(T v) : value(v) {}
};

template <class T, int D> struct Coords {
  vector<T> vec;
  //explicit Coords() {}
};
