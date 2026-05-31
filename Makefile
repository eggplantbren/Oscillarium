CXX = g++
CXXFLAGS = -O3 -march=native -Wall -Wextra -pedantic -Wno-unused-variable
INCLUDE = -I $(DNEST4_PATH) -I celerite2/c++/include -I /usr/include/eigen3
LINK = -L $(DNEST4_PATH)/DNest4/code

default:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c Data.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c MyModel.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c GaussianProcess.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c main.cpp
	$(CXX) $(LINK) -o main *.o -ldnest4 -lpthread
