CXX = g++
CXXFLAGS = -O3 -march=native -Wall -Wextra -pedantic

default:
	$(CXX) $(CXXFLAGS) -c Data.cpp
