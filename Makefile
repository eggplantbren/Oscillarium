CXX = g++
CXXFLAGS = -O3 -march=native -Wall -Wextra -pedantic
INCLUDE = -I $(DNEST4_PATH)

default:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c Data.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c MyModel.cpp
