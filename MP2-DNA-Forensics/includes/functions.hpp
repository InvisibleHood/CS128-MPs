#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
#include <string>
#include <fstream>

std::string DataMatch(std::string file, std::string dna);
std::vector<int> ParseDna(std::string dna, std::vector<std::string> str);

#endif