#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <map>
#include <string>

#include "db_table.hpp"

class Database {
 public:
  void CreateTable(const std::string& table_name);    //DONE
  void DropTable(const std::string& table_name);      //DONE
  DbTable& GetTable(const std::string& table_name);   //DONE

  Database() = default;    //DONE
  Database(const Database& rhs);       //DONE  
  Database& operator=(const Database& rhs);   //DONE  
  ~Database();     //DONE  
  friend std::ostream& operator<<(std::ostream& os, const Database& db);    //Done

 private:
  std::map<std::string, DbTable*> tables_;  // maps table name -> table      
};

//std::ostream& operator<<(std::ostream& os, const Database& db);

#endif