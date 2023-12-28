#include "db.hpp"

Database::Database(const Database& rhs) {            
    for (const auto& table: rhs.tables_) {
        tables_[table.first] = new DbTable (*table.second);    
        //*tables_[table.first] = *table.second;       
        //--we can not *tables_[table.first] b/c it is a nullptr;
    }
}


DbTable& Database::GetTable(const std::string& table_name) {
    return *tables_.at(table_name);
}

Database::~Database() {
    for (auto& table : tables_) {
        delete table.second;          // --when we invoke delete, it will automatically invoke ~DbTable;
        table.second = nullptr;
    }
    tables_.clear();
}

Database& Database::operator=(const Database& rhs) {  
    if (&rhs == this) {        
        return *this;
    }
    if (!tables_.empty()) {
        for (const auto& table : tables_) {
            delete table.second;
            //table.second = nullptr;     
        }
        tables_.clear();
    }
    for (const auto& table: rhs.tables_) {
        tables_[table.first] = new DbTable(*table.second);     
    }
    return *this;
}


void Database::DropTable(const std::string& table_name) {          
    if (!tables_.contains(table_name)) {
        throw table_name;
    }
    delete tables_.at(table_name);
    tables_.erase(table_name);        
}

void Database::CreateTable(const std::string& table_name) {  
    tables_[table_name] = new DbTable();
    // tables_.insert({table_name, new DbTable});      
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
    for (const auto& table : db.tables_) {
        os << table.first << "\n";
    }
    return os;
}