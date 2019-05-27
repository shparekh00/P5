#makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -g

all: test_index_min_pq

test_index_min_pq: test_index_min_pq.o
	$(CXX) $(CXXFLAGS) -o test_index_min_pq test_index_min_pq.o -pthread -lgtest

clean:
	rm test_index_min_pq test_index_min_pq.o

