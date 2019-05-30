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

  impq.Pop();
  impq.Pop();

  EXPECT_THROW(impq.Pop(), std::underflow_error);
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

// mihir's cases

/*
  Double Suite
 * Note: Only chosen set of doubles used
 * Ascending order of doubles used:
 * 1.0 < 1.2 < 2.2 < 25.2 < 42.5 < 43.5 < 51.0 < 60.3 < 74.32 < 76.12 < 85.0
*/



TEST(DoubleIndexMinPQ, PushExistingIndexException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyvalfirst{
          { 2.2, 99},
          { 51.0, 54},
          { 42.5, 53},
          { 74.32, 93},
          { 1.2, 40},
          { 85.0, 10},
          { 43.5, 20},
          { 76.12, 41},
          { 25.2, 50},
          { 60.3, 89},
  };

  for (auto &i : keyvalfirst) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Index 50 already exists and should throw an exception
  EXPECT_THROW(impq.Push(23.2, 50), std::exception);
}


TEST(DoubleIndexMinPQ, SimplePop) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 42.5, 53},
          { 74.32, 93},
          { 1.2, 40},
          { 85.0, 10},
          { 43.5, 20},
          { 76.12, 41},
          { 25.2, 50},
          { 60.3, 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

  while (impq.Size()) {
    impq.Pop();
  }

  // Size of the queue should now be 0
  EXPECT_EQ(impq.Size(), 0);

  // Test Contains() on the now empty queue
  EXPECT_FALSE(impq.Contains(99));
  EXPECT_FALSE(impq.Contains(54));
  EXPECT_FALSE(impq.Contains(53));
  EXPECT_FALSE(impq.Contains(93));
  EXPECT_FALSE(impq.Contains(40));
  EXPECT_FALSE(impq.Contains(10));
  EXPECT_FALSE(impq.Contains(20));
  EXPECT_FALSE(impq.Contains(41));
  EXPECT_FALSE(impq.Contains(50));
  EXPECT_FALSE(impq.Contains(89));
}


TEST(DoubleIndexMinPQ, PopOverflowException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 42.5, 53},
          { 74.32, 93},
          { 1.2, 40},
          { 85.0, 10},
          { 43.5, 20},
          { 76.12, 41},
          { 25.2, 50},
          { 60.3, 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

  while (impq.Size()) {
    impq.Pop();
  }

  // Size of the queue should now be 0
  EXPECT_EQ(impq.Size(), 0);

  // The queue should now be empty,
  // calling Pop() should throw an exception
  EXPECT_THROW(impq.Pop(), std::exception);
}


TEST(DoubleIndexMinPQ, SimpleContains) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 42.5, 53},
          { 74.32, 93},
          { 1.2, 40},
          { 85.0, 10},
          { 43.5, 20},
          { 76.12, 41},
          { 25.2, 50},
          { 60.3, 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));
}


TEST(DoubleIndexMinPQ, ContainsException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
      { 2.2, 99},
      { 51.0, 54},
      { 42.5, 53},
      { 74.32, 93},
      { 1.2, 40},
      { 85.0, 10},
      { 43.5, 20},
      { 76.12, 41},
      { 25.2, 50},
      { 60.3, 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

// Should throw an exception when index is greater than capacity
EXPECT_THROW(impq.Contains(101), std::exception);
}


TEST(DoubleIndexMinPQ, SimpleChangeKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 74.32, 93},
          { 1.2, 40},
          { 43.5, 20},
          { 76.12, 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (1.2, 40)
  EXPECT_EQ(impq.Top(), 40);

  // Test ChangeKey(): change key associated to value 41
  impq.ChangeKey(1.0, 41);

  // Key-value at the top should now be (1.0, 41)
  EXPECT_EQ(impq.Top(), 41);
}


TEST(DoubleIndexMinPQ, ChangeKeyInvalidException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 74.32, 93},
          { 1.2, 40},
          { 43.5, 20},
          { 76.12, 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (1.2, 40)
  EXPECT_EQ(impq.Top(), 40);

  // Throw exception since index 101 is greater than capacity
  EXPECT_THROW(impq.ChangeKey(1.0, 101), std::exception);
}


TEST(DoubleIndexMinPQ, ChangeKeyDoesntExistException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<double, int>> keyval{
          { 2.2, 99},
          { 51.0, 54},
          { 74.32, 93},
          { 1.2, 40},
          { 43.5, 20},
          { 76.12, 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (1.2, 40)
  EXPECT_EQ(impq.Top(), 40);

  // Throw exception since index 30 doesn't exist
  EXPECT_THROW(impq.ChangeKey(1.0, 30), std::exception);
}


/*
  String Suite
 * Note: Only chosen set of strings used
 * Lexicographical order of strings used:
 * "Adam" < "Bruce" < "Clint" < "Ego" < "Loki" < "Natasha" < "Steve"
 * < "Thanos" < "Thor" < "Tony" < "Ultron" < "Wanda"
*/


TEST(StringIndexMinPQ, SimpleScenario) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
          { std::string("Clint"), 99},
          { std::string("Steve"), 54},
          { std::string("Loki"), 53},
          { std::string("Thor"), 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (std::string("Clint"), 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  // Test Contains()
  EXPECT_TRUE(impq.Contains(93));

  // Key-value at the top should now be (std::string("Loki"), 53)
  EXPECT_EQ(impq.Top(), 53);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey(std::string("Bruce"), 93);

  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 93);
}


TEST(StringIndexMinPQ, ComplexScenario) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
          { std::string("Clint"), 99},
          { std::string("Steve"), 54},
          { std::string("Loki"), 53},
          { std::string("Thor"), 93},
          { std::string("Bruce"), 40},
          { std::string("Ultron"), 10},
          { std::string("Natasha"), 20},
          { std::string("Tony"), 41},
          { std::string("Ego"), 50},
          { std::string("Thanos"), 89},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (std::string("Clint"), 99)
  EXPECT_EQ(impq.Top(), 40);
  impq.Pop();

  // Test Contains()
  EXPECT_TRUE(impq.Contains(10));

  // Key-value at the top should now be (std::string("Loki"), 53)
  EXPECT_EQ(impq.Top(), 99);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey(std::string("Adam"), 10);

  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 10);

  impq.Pop();

  EXPECT_EQ(impq.Top(), 99);
}


TEST(StringIndexMinPQ, SimpleTop) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
          { std::string("Clint"), 99},
          { std::string("Steve"), 54},
          { std::string("Loki"), 53},
          { std::string("Thor"), 93},
          { std::string("Bruce"), 40},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 5
  EXPECT_EQ(impq.Size(), 5);

  // Key-value at the top should now be (std::string("Bruce"), 40)
  EXPECT_EQ(impq.Top(), 40);
  impq.Pop();

  // Key-value at the top should now be (std::string("Clint"), 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  // Key-value at the top should now be (std::string("Loki"), 53)
  EXPECT_EQ(impq.Top(), 53);
  impq.Pop();

  // Key-value at the top should now be (std::string("Steve"), 54)
  EXPECT_EQ(impq.Top(), 54);
  impq.Pop();

  // Key-value at the top should now be (std::string("Thor"), 93)
  EXPECT_EQ(impq.Top(), 93);
  impq.Pop();

  // Size of the queue should now be 0
  EXPECT_EQ(impq.Size(), 0);
}


TEST(StringIndexMinPQ, TopException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 5
  EXPECT_EQ(impq.Size(), 5);

  // Key-value at the top should now be (std::string("Bruce"), 40)
  EXPECT_EQ(impq.Top(), 40);
  impq.Pop();

  // Key-value at the top should now be (std::string("Clint"), 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();

  // Key-value at the top should now be (std::string("Loki"), 53)
  EXPECT_EQ(impq.Top(), 53);
  impq.Pop();

  // Key-value at the top should now be (std::string("Steve"), 54)
  EXPECT_EQ(impq.Top(), 54);
  impq.Pop();

  // Key-value at the top should now be (std::string("Thor"), 93)
  EXPECT_EQ(impq.Top(), 93);
  impq.Pop();

  // Size of the queue should be now be 0
  EXPECT_EQ(impq.Size(), 0);

  // Queue should be empty
  EXPECT_THROW(impq.Top(), std::exception);
}


TEST(StringIndexMinPQ, SimplePush) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains()
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));
}


TEST(StringIndexMinPQ, PushOverflowException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(10);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyvalfirst{
    { std::string("Clint"), 9},
    { std::string("Steve"), 4},
    { std::string("Loki"), 5},
    { std::string("Thor"), 3},
    { std::string("Bruce"), 2},
    { std::string("Ultron"), 1},
    { std::string("Natasha"), 0},
    { std::string("Tony"), 6},
    { std::string("Ego"), 7},
    { std::string("Thanos"), 8},
  };

  for (auto &i : keyvalfirst) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);


  // Queue should be full and should throw an exception is a Push() is attempted
  EXPECT_THROW(impq.Push(std::string("Wanda"), 0), std::exception);
}


TEST(StringIndexMinPQ, PushExistingIndexException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyvalfirst{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyvalfirst) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Index 50 already exists and should throw an exception
  EXPECT_THROW(impq.Push(std::string("Wanda"), 50), std::exception);
}


TEST(StringIndexMinPQ, SimplePop) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

  while (impq.Size()) {
    impq.Pop();
  }

  // Size of the queue should now be 0
  EXPECT_EQ(impq.Size(), 0);

  // Test Contains() on the now empty queue
  EXPECT_FALSE(impq.Contains(99));
  EXPECT_FALSE(impq.Contains(54));
  EXPECT_FALSE(impq.Contains(53));
  EXPECT_FALSE(impq.Contains(93));
  EXPECT_FALSE(impq.Contains(40));
  EXPECT_FALSE(impq.Contains(10));
  EXPECT_FALSE(impq.Contains(20));
  EXPECT_FALSE(impq.Contains(41));
  EXPECT_FALSE(impq.Contains(50));
  EXPECT_FALSE(impq.Contains(89));
}


TEST(StringIndexMinPQ, PopOverflowException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

  while (impq.Size()) {
    impq.Pop();
  }

  // Size of the queue should now be 0
  EXPECT_EQ(impq.Size(), 0);

  // The queue should now be empty,
  // calling Pop() should throw an exception
  EXPECT_THROW(impq.Pop(), std::exception);
}


TEST(StringIndexMinPQ, SimpleContains) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));
}


TEST(StringIndexMinPQ, ContainsException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Loki"), 53},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Ultron"), 10},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
    { std::string("Ego"), 50},
    { std::string("Thanos"), 89},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Size of the queue should be 10
  EXPECT_EQ(impq.Size(), 10);

  // Test Contains() on all the elements
  EXPECT_TRUE(impq.Contains(99));
  EXPECT_TRUE(impq.Contains(54));
  EXPECT_TRUE(impq.Contains(53));
  EXPECT_TRUE(impq.Contains(93));
  EXPECT_TRUE(impq.Contains(40));
  EXPECT_TRUE(impq.Contains(10));
  EXPECT_TRUE(impq.Contains(20));
  EXPECT_TRUE(impq.Contains(41));
  EXPECT_TRUE(impq.Contains(50));
  EXPECT_TRUE(impq.Contains(89));

  // Should throw an exception when index is greater than capacity
  EXPECT_THROW(impq.Contains(101), std::exception);
}


TEST(StringIndexMinPQ, SimpleChangeKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (std::string("Bruce"), 40)
  EXPECT_EQ(impq.Top(), 40);

  // Test ChangeKey(): change key associated to value 41
  impq.ChangeKey(std::string("Adam"), 41);

  // Key-value at the top should now be (std::string("Adam"), 41)
  EXPECT_EQ(impq.Top(), 41);
}


TEST(StringIndexMinPQ, ChangeKeyInvalidException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (std::string("Bruce"), 40)
  EXPECT_EQ(impq.Top(), 40);

  // Throw exception since index 101 is greater than capacity
  EXPECT_THROW(impq.ChangeKey(std::string("Adam"), 101), std::exception);
}


TEST(StringIndexMinPQ, ChangeKeyDoesntExistException) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<std::string> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<std::string, int>> keyval{
    { std::string("Clint"), 99},
    { std::string("Steve"), 54},
    { std::string("Thor"), 93},
    { std::string("Bruce"), 40},
    { std::string("Natasha"), 20},
    { std::string("Tony"), 41},
  };

  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }

  // Key-value at the top should now be (std::string("Bruce"), 40)
  EXPECT_EQ(impq.Top(), 40);

  // Throw exception since index 30 doesn't exist
  EXPECT_THROW(impq.ChangeKey(std::string("Adam"), 30), std::exception);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

