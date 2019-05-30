#makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -g

# all: test_index_min_pq prim_mst

# test_index_min_pq: test_index_min_pq.o
	# $(CXX) $(CXXFLAGS) -o test_index_min_pq test_index_min_pq.o -pthread -lgtest

prim_mst: prim_mst.o
	$(CXX) $(CXXFLAGS) -o prim_mst prim_mst.o

clean:
	# rm test_index_min_pq test_index_min_pq.o
	rm prim_mst prim_mst.o

