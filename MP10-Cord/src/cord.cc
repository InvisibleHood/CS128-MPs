#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv) {
    if (sv.empty()) {
        throw sv;
    }
    data_ = new char [sv.size() + 1] ();
    std::copy(sv.begin(), sv.end(),data_);
    length_ = static_cast<unsigned int>(sv.size());
}

Cord::~Cord() {
    delete[] data_;
    data_ = nullptr;
}

SharedPointer<char> Cord::ToString() const { 
    if (length_ == 0) {
        return SharedPointer<char>{};
    }    
    if (data_ == nullptr) {
        std::string str;
        CordWalk(left_, str);
        CordWalk(right_, str);
        char* string = new char [str.size() + 1] ();
        for (unsigned int i = 0; i < str.size() + 1; i++) {
            if (i == str.size()) {
                string[i] = '\0';
                break;
            }
            string[i] = str[i];
        }
        SharedPointer<char> array(string, kSharedPointerType::kArray);
        return array;
    } 
    char* copy = new char [length_ + 1] ();
    for (unsigned int i = 0; i < length_ + 1; i++) {
        if (i == length_) {
            copy[i] = '\0';
            break;
        }
        copy[i] = data_[i];
    }
    SharedPointer<char> output(copy, kSharedPointerType::kArray);
    return output;
}

void Cord::CordWalk(SharedPointer<Cord> kSpcord, std::string& str) const {
    if (kSpcord.Get() != nullptr) {
        if (kSpcord->data_ == nullptr) {
            CordWalk(kSpcord.Get()->left_, str);
            CordWalk(kSpcord.Get()->right_, str);
        } else {
            for (const char& c : kSpcord.Get()->Data()) {
                str += c;
            }
        }
    }
}

// SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
//     if (left_cord.Get()  == nullptr || right_cord.Get() == nullptr) {
//         throw;
//     }
//     Cord* concat = new Cord ();
//     concat->left_ = left_cord;
//     concat->right_ = right_cord;
//     concat->length_ = left_cord->length_ + right_cord->length_;
//     SharedPointer<Cord> output = concat;
//     return output;
// }