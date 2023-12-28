#include "functions.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

std::vector<int> ParseDna(std::string dna, std::vector<std::string> str) {
  std::vector<int> output;
  for (size_t i = 1; i < str.size(); ++i) {
    int largest = 0;
    int number = 0;
    size_t pos = dna.find(str.at(i));
    if (pos == std::string::npos) {
      return output;
    }
    while (pos + str.at(i).size() <= dna.size()) {
      std::string temp_str = dna.substr(pos, str.at(i).size());
      if ((temp_str.compare(str.at(i))) == 0) {
        number++;
        pos = pos + str.at(i).size();
        //std::cout << "POS" << pos << std::endl;
        //std::cout << "largest  " << largest << std::endl;
        if (pos == dna.size() && number > largest) {
          largest = number;
        }
      } else {
        if (number > largest) {
          largest = number;
        }
        number = 0;
        pos++;
      }
    }
    //std::cout << "LARGEST" << largest << std::endl;
    output.push_back(largest);
  }
  return output;
}

std::string DataMatch(std::string file, std::string dna) {
  std::ifstream ifs{file};
  std::vector<std::string> name_and_str;
  std::vector<std::vector<std::string>> name_nums;
  int line_num = 0;
  for (std::string line; std::getline(ifs, line); line = "") {
    if (line_num == 0) {
      //std::cout << "line = \"" << line << '\"' << std::endl;
      name_and_str = utilities::GetSubstrs(line, ',');
    } else {
      //std::cout << "line = \"" << line << '\"' << std::endl;
      std::vector<std::string> nn_vec = utilities::GetSubstrs(line, ',');
      name_nums.push_back(nn_vec);
    }
    line_num++;
  }
  std::vector<int> str_nums = ParseDna(dna, name_and_str);
  //std::cout << "STRNUMS SIZE   " << str_nums.size() << '\"' << std::endl;
  if (str_nums.size() != name_and_str.size() - 1) {
    return "No match";
  }
  std::vector<std::string> dna_owner;
  for (size_t i = 0; i < name_nums.size(); ++i) {
    size_t j = 1;
    while (j < name_nums.at(i).size()) {
      if (std::stoi(name_nums.at(i).at(j)) != str_nums.at(j - 1)) {
        break;
      }
      if (j == str_nums.size()) {
        dna_owner.push_back(name_nums.at(i).at(0));
      }
      j++;
    }
  }
  if (dna_owner.size() == 1) {
    return dna_owner.at(0);
  }
  return "No match";
}