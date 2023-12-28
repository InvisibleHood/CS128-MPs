CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests
undefined: bin/undefined
bin/exec: ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc ./includes/cord.hpp ./includes/cord_utilities.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc -o $@

bin/tests: ./tests/tests.cc ./src/cord.cc ./src/cord_utilities.cc ./includes/cord.hpp ./includes/cord_utilities.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/cord.cc ./src/cord_utilities.cc -o $@

bin/undefined: ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc ./includes/cord.hpp ./includes/cord_utilities.hpp ./includes/shared_pointer.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc -fsanitize=undefined -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests undefined 

clean:
	rm -fr bin/* 
