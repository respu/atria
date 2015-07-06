// Copyright: 2014, 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/into.hpp>
#include <atria/xform/reducing/first_rf.hpp>
#include <atria/xform/transducer/partition.hpp>
#include <atria/testing/spies.hpp>
#include <atria/testing/gtest.hpp>

namespace atria {
namespace xform {

TEST(into, partition)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5, 6 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5, 6}
      }));
}

TEST(into, partition_flushing)
{
  auto v = std::vector<int> { 1, 2, 3, 4, 5 };

  auto res = into(std::vector<std::vector<int> > {}, partition(2u), v);
  EXPECT_EQ(res, (std::vector<std::vector<int> > {
        {1, 2}, {3, 4}, {5}
      }));
}

TEST(into, partition_does_not_copy_step_function)
{
  auto step = testing::copy_spy<first_rf_t>{};

  auto v = std::vector<int> { 1, 2, 3, 4, 5 };
  reduce(partition(2u)(step), 0, v);
  EXPECT_EQ(step.copied.count(), 2);
}

} // namespace xform
} // namespace atria
