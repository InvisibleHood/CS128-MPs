#include <iostream>

#include "cord_utilities.hpp"
#include "cord.hpp"

int main() {
  // SharedPointer<Cord> a = new Cord("CS_");
  // SharedPointer<Cord> b = new Cord("128_");
  // SharedPointer<Cord> c1 = ConcatCords(a, b);
  // auto b_str = c1->ToString();
  // std::cout << b_str.Get() << std::endl;
  // char c[] = {'c', 'a', 'w', 'c' , '2'};    
  // std::cout << c << std::endl;      // it can convert the char array into strings and print it out. 
  // SharedPointer<Cord> c = ConcatCords(a, b);

  // auto c_str = c->ToString();
  // std::cout << c_str.Get() << std::endl;

  // auto res = SubString(c, 0, 3);
  // auto res_str = res->ToString();
  // std::cout << res_str.Get() << std::endl;


  // SharedPointer<Cord> s1 = new Cord("ab");
  // SharedPointer<Cord> s2 = new Cord("c");
  // SharedPointer<Cord> s3 = new Cord("de");
  // SharedPointer<Cord> s4 = new Cord("fg");
  // SharedPointer<Cord> s5 = new Cord("hi");
  // SharedPointer<Cord> s6 = new Cord("jk");
  // SharedPointer<Cord> s7 = new Cord("l");

  // SharedPointer<Cord> c1 = ConcatCords(s1, s2);
  // SharedPointer<Cord> c2 = ConcatCords(c1, s3);
  // SharedPointer<Cord> c3 = ConcatCords(s4, s5);
  // SharedPointer<Cord> c4 = ConcatCords(s6, s7);
  // SharedPointer<Cord> c5 = ConcatCords(c3, c4);
  // SharedPointer<Cord> c6 = ConcatCords(c2, c5);
  // // auto c3ts = c6->ToString();
  // // std::cout << c3ts.Get() << std::endl;


  // auto sub = SubString(c6, 10, 12);
  // auto sub_str = sub->ToString();
  // std::cout << sub_str.Get() << std::endl;

  SharedPointer<Cord> s1 = new Cord("he");
  SharedPointer<Cord> s2 = new Cord("llo");
  SharedPointer<Cord> s3 = new Cord("wor");
  SharedPointer<Cord> s4 = new Cord("ld");

  SharedPointer<Cord> c1 = ConcatCords(s1, s2);
  SharedPointer<Cord> c2 = ConcatCords(s3, s4);
  SharedPointer<Cord> c3 = ConcatCords(c1, c2);

  auto sub = SubString(c3, 2, 8);
  auto sub2 = SubString(c3, 2, 7);
  auto sub_str2 = sub2->ToString();
  std::cout << sub_str2.Get() << std::endl;
  auto sub_str = sub->ToString();
  std::cout << sub_str.Get() << std::endl;
}