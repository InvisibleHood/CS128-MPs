#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  DbTable db;
  db.AddColumn({"FIRST", DataType::kInt});
  std::cout << db;
  // write informal tests here
}