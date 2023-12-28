CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/illini_book.cc ./includes/illini_book.hpp ./src/utilities.cc ./includes/utilities.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc -o $@

bin/tests: ./tests/tests.cc ./src/illini_book.ccc ./includes/illini_book.hpp ./src/utilities.cc ./includes/utilities.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/illini_book.cc ./src/utilities.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf ./bin/*
