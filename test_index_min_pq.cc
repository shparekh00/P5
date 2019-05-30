#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "index_min_pq.h"

/* Test cases for doubles */

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

TEST(IndexMinPQ, Overflow) {
  // Indexed min-priority queue of capacity 4
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

  EXPECT_THROW(impq.Push(7.7, 102), std::overflow_error);
}

TEST(IndexMinPQ, RepeatValue) {
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

  EXPECT_THROW(impq.Push(7.7, 99), std::runtime_error);
}

TEST(IndexMinPQ, RepeatKey) {
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

  impq.Push(2.2, 24);

  EXPECT_EQ(impq.Top(), 99);
}

TEST(IndexMinPQ, Underflow) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  while (impq.Size()) {
    impq.Pop();
  }
  // pop extra time
  EXPECT_THROW(impq.Pop(), std::underflow_error);
}

TEST(IndexMinPQ, SimpleChangeKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 3.1, 32},
          { 7.3, 24}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top: 2.2
  EXPECT_EQ(impq.Top(), 99);

  // Test ChangeKey(): change key associated to value 32
  impq.ChangeKey(1.0, 32);

  // Key-value at the top:(1.0, 32)
  EXPECT_EQ(impq.Top(), 32);
}

TEST(IndexMinPQ, ChangeKeyIdxOutofBounds) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.ChangeKey(2.2, 102), std::overflow_error);
}

TEST(IndexMinPQ, ChangeKeyNonexistent) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.ChangeKey(1.0, 52), std::runtime_error);
}

TEST(IndexMinPQ, SimplePop) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 3.1, 32}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(32));

  while (impq.Size()) {
    impq.Pop();
  }

  EXPECT_FALSE(impq.Contains(99));
  EXPECT_FALSE(impq.Contains(54));
  EXPECT_FALSE(impq.Contains(32));
}

TEST(IndexMinPQ, SimplePush) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, unsigned int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 3.1, 32},
          { 7.3, 24}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(32));
  EXPECT_TRUE(impq.Contains(24));

}




/*Test cases for ints*/

TEST(IntMinPQ, SimpleScenario) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 42, 53},
          { 74, 93}
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
  impq.ChangeKey(1, 93);
  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 93);
}

TEST(IntMinPQ, Overflow) {
  // Indexed min-priority queue of capacity 4
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 42, 53},
          { 74, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.Push(7, 102), std::overflow_error);
}

TEST(IntMinPQ, RepeatValue) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 42, 53},
          { 74, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.Push(7, 99), std::runtime_error);
}

TEST(IntMinPQ, RepeatKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 42, 53},
          { 74, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  impq.Push(2, 24);

  EXPECT_EQ(impq.Top(), 99);
}

TEST(IntMinPQ, Underflow) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  while (impq.Size()) {
    impq.Pop();
  }
  // pop extra time
  EXPECT_THROW(impq.Pop(), std::underflow_error);
}

TEST(IntMinPQ, SimpleChangeKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 3, 32},
          { 7, 24}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top: 2.2
  EXPECT_EQ(impq.Top(), 99);

  // Test ChangeKey(): change key associated to value 32
  impq.ChangeKey(1, 32);

  // Key-value at the top:(1.0, 32)
  EXPECT_EQ(impq.Top(), 32);
}

TEST(IntMinPQ, ChangeKeyIdxOutofBounds) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.ChangeKey(2, 102), std::overflow_error);
}

TEST(IntMinPQ, ChangeKeyNonexistent) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_THROW(impq.ChangeKey(1, 52), std::runtime_error);
}

TEST(IntMinPQ, SimplePop) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 3, 32}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(32));

  while (impq.Size()) {
    impq.Pop();
  }

  EXPECT_FALSE(impq.Contains(99));
  EXPECT_FALSE(impq.Contains(54));
  EXPECT_FALSE(impq.Contains(32));
}

TEST(IntMinPQ, SimplePush) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<unsigned int> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<unsigned int, unsigned int>> keyval{
          { 2, 99},
          { 51, 54},
          { 3, 32},
          { 7, 24}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(32));
  EXPECT_TRUE(impq.Contains(24));
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

