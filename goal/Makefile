CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g -ggdb

reverse: reverse.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f reverse
