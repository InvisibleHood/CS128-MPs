#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;

DbTable::DbTable(const DbTable& rhs) {
    for (unsigned int i = 0; i < rhs.col_descs_.size(); i++) {       //copy column vector
        col_descs_.push_back(rhs.col_descs_.at(i));
    }
    next_unique_id_ = rhs.next_unique_id_;
    for (unsigned int key = 0; key < rhs.rows_.size(); key++) {     // copy the map
        void** nrow = new void* [rhs.row_col_capacity_];
        for (unsigned int r = 0; r < rhs.col_descs_.size(); r++) {
            if (rhs.col_descs_.at(r).second == DataType::kDouble) {
                double d = *(static_cast<double*>(rhs.rows_.at(key)[r]));
                nrow[r] = static_cast<void*>(new double (d));
            } else if (rhs.col_descs_.at(r).second == DataType::kString) {
                std::string s = *(static_cast<std::string*>(rhs.rows_.at(key)[r]));
                nrow[r] = static_cast<void*>(new std::string (s));
            } else {
                int i = *(static_cast<int*>(rhs.rows_.at(key)[r]));
                nrow[r] = static_cast<void*>(new int (i));
            }
        }
        rows_[key] = nrow;
    }
    row_col_capacity_ = rhs.row_col_capacity_;
}

DbTable& DbTable::operator=(const DbTable& rhs) {      
    if (&rhs == this) {              
        return *this;
    }
    // delete this;
    for (unsigned int key = 0; key < rows_.size(); key++) {      // clear map
        for (unsigned int r = 0; r < col_descs_.size(); r++) {
            DataType d = col_descs_.at(r).second;
            if (d == DataType::kString) {
                delete static_cast<std::string*>(rows_.at(key)[r]);
            } else if (d == DataType::kDouble) {
                delete static_cast<double*>(rows_.at(key)[r]);
            } else {
                delete static_cast<int*>(rows_.at(key)[r]);
            }
        }
        delete[] rows_.at(key);
        rows_.at(key) = nullptr;
    }  
    rows_.clear();                  
    col_descs_ = rhs.col_descs_;     // clear and copy the vector
    row_col_capacity_ = rhs.row_col_capacity_;
    next_unique_id_ = rhs.next_unique_id_;
    for (unsigned int key = 0; key < rhs.rows_.size(); key++) {       //copy the void** in the map
        void** row = new void* [row_col_capacity_];
        for (unsigned int idx_row = 0; idx_row < rhs.col_descs_.size(); idx_row++) {  
            if (rhs.col_descs_[idx_row].second == DataType::kInt) {
                row[idx_row] = static_cast<void*>(new int (*(static_cast<int*>(rhs.rows_.at(key)[idx_row]))));
            } else if (rhs.col_descs_[idx_row].second == DataType::kDouble) {
                row[idx_row] = static_cast<void*>(new double (*(static_cast<double*>(rhs.rows_.at(key)[idx_row]))));
            } else if (rhs.col_descs_[idx_row].second == DataType::kString) {
                row[idx_row] = static_cast<void*>(new std::string (*(static_cast<std::string*>(rhs.rows_.at(key)[idx_row]))));
            }
        }
        rows_[key] = row;                
    }
    return *this;
}

DbTable::~DbTable() {     
    for(std::pair<unsigned int, void**> p : rows_) {
        for (unsigned int i= 0; i < col_descs_.size(); ++i) {
            DataType d = col_descs_.at(i).second;
            if (d == DataType::kDouble) {
                delete static_cast<double*>(p.second[i]);
            } else if (d == DataType::kInt) {
                delete static_cast<int*>(p.second[i]);
            } else {
                delete static_cast<std::string*>(p.second[i]);
            }
        }
        delete[] p.second;
        p.second = nullptr;
    }
    rows_.clear();
    // for (unsigned int key = 0; key < rows_.size(); key++) {      // clear map
    //     for (unsigned int r = 0; r < col_descs_.size(); r++) {
    //         DataType d = col_descs_.at(r).second;
    //         if (d == DataType::kString) {
    //             delete static_cast<std::string*>(rows_.at(key)[r]);
    //         } else if (d == DataType::kDouble) {
    //             delete static_cast<double*>(rows_.at(key)[r]);
    //         } else {
    //             delete static_cast<int*>(rows_.at(key)[r]);
    //         }
    //     }
    //     delete[] rows_.at(key);
    //     rows_.at(key) = nullptr;
    // }  
    // rows_.clear();                  
}


//======================================================== ADD && DELETE COLUMN 

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
    if (col_descs_.size() == row_col_capacity_) {
        row_col_capacity_ = row_col_capacity_ * 2;
        for (auto& row : rows_) {
            void** new_row = new void*[row_col_capacity_];
            for (unsigned int i = 0; i < col_descs_.size(); i++) {
                if (col_descs_.at(i).second == DataType::kDouble) {
                    new_row[i] = static_cast<void*>(new double(*(static_cast<double*>(row.second[i]))));
                    delete (static_cast<double*>(row.second[i]));
                } else if (col_descs_.at(i).second == DataType::kString) {
                    new_row[i] = static_cast<void*>(new std::string (*(static_cast<std::string*>(row.second[i]))));
                    delete (static_cast<std::string*>(row.second[i]));
                } else {
                    new_row[i] = static_cast<void*>(new int (*(static_cast<int*>(row.second[i]))));
                    delete (static_cast<int*>(row.second[i]));
                }
            }
            delete[] row.second;
            row.second = new_row;
        }
    }
    col_descs_.push_back(col_desc);
    for (unsigned int k = 0; k < rows_.size(); k++) {      
        if (col_desc.second == DataType::kString) {
            rows_.at(k)[col_descs_.size() - 1] = static_cast<void*>(new std::string(""));
        } else if (col_desc.second == DataType::kDouble) {
            rows_.at(k)[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
        } else {
            rows_.at(k)[col_descs_.size() - 1] = static_cast<void*>(new int(0));
        }
    }
}
void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
    if (col_idx >= col_descs_.size()) {
       throw std::out_of_range("INVALID COL_IDX");
    }
    if (col_descs_.size() == 1 && !rows_.empty()) {
        throw std::runtime_error("any table with at least one row must have at least one column.");
    }
    for (auto& row : rows_) {
        DataType dt = col_descs_.at(col_idx).second;
        if (dt == DataType::kDouble) {
            delete (static_cast<double*>(row.second[col_idx]));
        } else if (dt == DataType::kString) {
            delete (static_cast<std::string*>(row.second[col_idx]));
        } else {delete (static_cast<int*>(row.second[col_idx]));}
    }
    for (auto& row : rows_) {
        for (unsigned int i = col_idx + 1; i < col_descs_.size(); i++) {
            row.second[i - 1]  = row.second[i];
            if (i == col_descs_.size() - 1) {
                row.second[i] = nullptr;
            }
        }
    }
    col_descs_.erase(col_descs_.begin() + col_idx);
}

//================================================================ ADD && DELETE ROW

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
    if (col_data.size() != col_descs_.size()) {
        throw std::invalid_argument("WRONG COL_DATA");
    }
    void** row = new void* [col_data.size()];
    rows_[next_unique_id_] = row;
    int num = 0;
    for (const std::string& str : col_data) {
        switch (col_descs_.at(num).second) {
            case DataType::kDouble:
                rows_.at(next_unique_id_)[num] = static_cast<void*>(new double(std::stod(str)));
                break;
            case DataType::kInt:
                rows_.at(next_unique_id_)[num] = static_cast<void*>(new int(std::stoi(str)));
                break;
            case DataType::kString:
                rows_.at(next_unique_id_)[num] = static_cast<void*>(new std::string(str));
                break;
        }
        num++;
    }
    next_unique_id_++;
}

void DbTable::DeleteRowById(unsigned int id) {
    if (!rows_.contains(id)) {
       throw id;
    }
    for (unsigned r = 0; r < col_descs_.size(); r++) {
        if (col_descs_.at(r).second == DataType::kDouble) {
            delete (static_cast<double*>(rows_.at(id)[r]));
        } else if (col_descs_.at(r).second == DataType::kString) {
            delete (static_cast<std::string*>(rows_.at(id)[r]));
        } else {
            delete (static_cast<int*>(rows_.at(id)[r]));
        }
    }
    delete[] rows_.at(id);
    rows_.erase(id);
}

//==========================================================OPERATORS

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
    for (unsigned int i = 0; i < table.col_descs_.size(); i++) {
        os << table.col_descs_.at(i).first;
        if (table.col_descs_.at(i).second == DataType::kDouble) {
           os << "(double)";
        } else if (table.col_descs_.at(i).second == DataType::kString) {
            os << "(std::string)";
        } else {
            os << "(int)";
        }
        if (i == table.col_descs_.size() - 1) {
            os << "\n";
        } else {
            os << ", ";
        }
    }
    for (unsigned int key = 0; key < table.rows_.size(); key++) {         
        for (unsigned int r = 0; r < table.col_descs_.size(); r++) {
            if (table.col_descs_.at(r).second == DataType::kString) {
                os << *(static_cast<std::string*>(table.rows_.at(key)[r]));
            } else if (table.col_descs_.at(r).second == DataType::kDouble) {
                os << *(static_cast<double*>(table.rows_.at(key)[r]));
            } else {
                os << *(static_cast<int*>(table.rows_.at(key)[r]));
            }
            if (r != table.col_descs_.size() - 1) {
                os << ", ";
            }
        }
        os << "\n";
    }
    return os;
}