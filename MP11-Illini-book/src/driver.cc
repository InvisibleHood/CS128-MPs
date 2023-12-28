#include "illini_book.hpp"
#include <iostream>
#include <vector>


int main() {
  IlliniBook ib("/home/vagrant/src/mp11-illini-book-InvisibleHood/example/persons.csv", "/home/vagrant/src/mp11-illini-book-InvisibleHood/example/relations.csv");
  // bool n = ib.AreRelated(8,7);
  // if (n) {
  //   std::cout << "YEEHEHEHHEHEHEH" << std::endl;
  // } else {
  //   std::cout << "NOO" << std::endl;
  // }
  // const int kI = 6;
  // if (ib.AreRelated(7, kI, "124")) {
  //   std::cout << "YEEHEHEHHEHEHEH" << std::endl;
  // } else {
  //   std::cout << "NOO" << std::endl;
  // }

  //std::cout << ib.GetRelated(1,7) << std::endl;

  // std::vector<int> vect = ib.GetSteps(1,2);
  // for (auto& e : vect) {
  //   std::cout << e << std::endl;
  // }

  // int s = ib.GetRelated(6,2, "128");
  // std::cout << s << std::endl;

  std::vector<std::string> v = {"128", "124", "173"};
  std::cout << ib.CountGroups(v) << std::endl;

  return 0;
}


