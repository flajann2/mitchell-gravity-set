#include <atomic>
#include <merseberg>
#include "gtest/gtest.h"

namespace {
  TEST(merseberg_incantation, basic_test) {
    auto container = std::vector<int>{};
    for (int i = 0; i < 1137; ++i) {
      container.push_back(i);
    }

    auto sigma = [](auto begin, auto end) {
      int sum = 0;
      for (auto pi = begin; pi != end; ++pi) {
        sum += *pi;
      }
      return static_cast<int>(sum);
    };

    auto single = sigma(container.begin(), container.end());
    auto imp = merseberg::incantation(container);
    imp.invoke(sigma);
    imp.join();
    auto concurrent = imp([](auto res) {
      int s = 0;
      for (auto a : res) {
        s += a;
      }
      return s;
    });
    EXPECT_EQ(single, concurrent);
  }

  TEST(merseberg_incantation, setting_thread_count) {
    auto container = std::vector<int>{0, 1, 2, 3};

    auto imp = merseberg::incantation(container);
    imp.invoke([](auto, auto){ return 0; }, 2).join();
    EXPECT_EQ(2, imp.threads());


    auto imp2 = merseberg::incantation(container);
    imp2.invoke([](auto, auto){ return 0; }, 200).join();
    EXPECT_EQ(200, imp2.threads());
    
  }

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
