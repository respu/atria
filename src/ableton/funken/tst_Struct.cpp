// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <iostream>
#include <ableton/funken/Struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <unordered_set>
#include <string>
#include <gtest/gtest.h>

namespace ableton {
namespace funken {
namespace test {

struct Person : Struct<Person>
{
  std::string name;
  std::size_t age;

  Person(std::string name = "",
         std::size_t age  = 0)
    : name(name), age(age) {}
};

} // namespace test
} // namespace funken
} // namespace ableton

ABL_FUNKEN_STRUCT(
  ableton::funken::test::Person,
  (std::string, name)
  (std::size_t, age));

namespace ableton {
namespace funken {

TEST(Struct, CanPutInHashMap)
{
  using test::Person;
  std::unordered_set<Person> s;
  s.insert(Person { "peter", 42 });
  EXPECT_EQ(1, s.count(Person { "peter", 42 }));
  EXPECT_EQ(0, s.count(Person { "peter", 13 }));
  EXPECT_EQ(0, s.count(Person { "john", 42 }));
}

TEST(Struct, CanPutInMap)
{
  using test::Person;
  std::set<Person> s;
  s.insert(Person { "peter", 42 });
  EXPECT_EQ(1, s.count(Person { "peter", 42 }));
  EXPECT_EQ(0, s.count(Person { "peter", 13 }));
  EXPECT_EQ(0, s.count(Person { "john", 42 }));
}

TEST(Struct, InvalidateCache)
{
  using test::Person;
  auto x = Person { "john", 13 };
  auto y = Person { "peter", 13 };
  EXPECT_TRUE(x != y);
  auto z = y;
  z.name = "john";
  EXPECT_FALSE(x == z);
  modified(z);
  EXPECT_TRUE(x == z);
}

} // namespace funken
} // namespace ableton
