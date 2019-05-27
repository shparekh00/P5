#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "index_min_pq.h"

TEST(IndexMinPQ, SimpleScenario) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
    { 2.2, 99},
    { 51.0, 54},
    { 42.5, 53},
    { 74.32, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (2.2, 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  // Test Contains()
  EXPECT_TRUE(impq.Contains(93));

  // Key-value at the top should now be (42.5, 53)
  EXPECT_EQ(impq.Top(), 53);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey(1.0, 93);
  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 93);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

