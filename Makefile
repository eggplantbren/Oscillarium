CXX = g++
CXXFLAGS = -O3 -march=native -Wall -Wextra -pedantic
INCLUDE = -I $(DNEST4_PATH) -I celerite2/c++/include -I /usr/include/eigen3

default:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c Data.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c MyModel.cpp
