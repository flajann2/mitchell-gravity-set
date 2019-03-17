#include <compute>
#include <marching_tetrahedra>

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace std;
using namespace mgs;
using namespace mgs::march;

class ComputeTest : public testing::Test {
 public:
  double s = 32.2;
  Position c{3, 2.3, 22};
  Position cc;
  Position p{0.01, 5.53, -34.1};

  Bounds box;
  StarField field;
  MakeTesselation tess;

  virtual void SetUp() {
    box = Bounds {Coordinate{-10, -10, -10}, Coordinate{10, 10, 10}};
    field = StarField(box, 6, 3);
    tess = MakeTesselation(field);
  }
  
  virtual void TearDown() {}
  virtual void TestBody() {}

  void pr_coord(const string& prefix, const Position& c) {
    for (int v : c.vec) cout << prefix << ": " << v << '\n';
    cout << '\n';
  }

  void test_field() {
    Coordinate c{0.44, -0.95, 1};
    StarField f(Coordinate{-1, -1, -1}, Coordinate{1, 1, 1}, 32, 3);
    cout << "cube_size " << f.cube_size << '\n';
    cout << "actual size " << f.grid.size() << '\n';
    for (auto k = 0; k < f.cube_size; ++k) {
      for (auto j = 0; j < f.cube_size; ++j) {
        for (auto i = 0; i < f.cube_size; ++i) {
          Index idx{i, j, k};
          f[idx] = i * j * k;
          EXPECT_EQ(f[idx], i * j * k);
        }
      }
    }

    cout << f << '\n';

    f.coords2index(c);
  }

  void test_make_tesselation() {
    cout << "make tesselation[" << tess << "]\n";
    for (indexer_t i = 0; i < field.cube_size - 1; ++i){
      for (indexer_t j = 0; j < field.cube_size - 1; ++j){
        for (indexer_t k = 0; k < field.cube_size - 1; ++k){
          Index idx {i,j,k};
          auto t = tess.tesseltate_cube(idx);
          cout << "tesseract for " << idx << ": " << t << endl;
        }
      }
    }
  }

  void test_marching_tetraherda() {}
  
  void test_math_on_Vector() {
    Position p1{-1, 1, 0};
    Position p2{1, -1, 2};

    Position padded = p1 + p2;
    Position psubbed = p1 - p2;
    Position doub = p1 * 2.0;
    Position halved = p1 / 2.0;

    Position paddr{0, 0, 2};
    Position psubr{-2, 2, -2};
    Position doubr{-2, 2, 0};
    Position halfr{-0.5, 0.5, 0};

    EXPECT_EQ(padded, paddr);
    EXPECT_EQ(psubbed, psubr);
    EXPECT_EQ(doub, doubr);
    EXPECT_EQ(halved, halfr);
  }

};

TEST(ComputeTest, test_field) {
  ComputeTest ct;
  ct.test_field();
}

TEST(ComputeTest, test_math_on_Vector) {
  ComputeTest ct;
  ct.test_math_on_Vector();
}

TEST(ComputeTest, test_marching_tetraherda) {
  ComputeTest ct;
  ct.test_marching_tetraherda();
}

TEST(ComputeTest, test_make_tesselation) {
  ComputeTest ct;
  ct.test_make_tesselation();
}

TEST(Index, operator_plus) {
  Index idx{0,1,2};
  index_bits_t bits{0b101};
  Index result{1,1,3};
  EXPECT_EQ(idx+bits, result);

  index_bits_t bits2{0b010};
  Index result2{0,2,2};
  EXPECT_EQ(idx+bits2, result2); 
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
