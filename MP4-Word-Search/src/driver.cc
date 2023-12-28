#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("deaol", CheckDirection::kHorizontal);
  std::cout << wss.FindWord("deaol");
}