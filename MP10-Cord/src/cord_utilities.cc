#include "cord_utilities.hpp"


SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
    if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
        throw std::invalid_argument("INVALID LEFT AND RIGHT");
    }
    Cord* concat = new Cord ();
    concat->left_ = left_cord;
    concat->right_ = right_cord;
    concat->length_ = left_cord->length_ + right_cord->length_;
    // concat->data_ = new char [0]();
    SharedPointer<Cord> output = concat;
    return output;
}


SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
    if (lower_idx >= upper_idx || upper_idx > curr_cord->Length() || lower_idx < 0 || upper_idx < 0) {throw std::invalid_argument("INVALID BOUNDS");}
    //base case
    if (lower_idx == 0 && upper_idx == curr_cord->Length()) {   // this is a base case for if the rest of them are definitely included. If we put it inside of the leaf if statement, it will be concatenated with a new one after it. 
        return curr_cord;
    }
    if (curr_cord->Left().Get() == nullptr && curr_cord->Right().Get() == nullptr) {   //leaf node but has part of them need to be returned 
        if (upper_idx - lower_idx < curr_cord->Length()) {
            char* string = new char [upper_idx - lower_idx + 1] ();
            for (unsigned int i = 0; i < upper_idx - lower_idx; i++) {
                string[i] = curr_cord->Data()[i + lower_idx];
            }
            string[upper_idx - lower_idx] = '\0';
            // std::string_view str = curr_cord->Data().substr(lower_idx, upper_idx);
            Cord* output = new Cord(string);
            return SharedPointer<Cord>{output};
        }
    } 

    //recursive steps 
    if (upper_idx <= curr_cord->Left()->Length()) { // all at left  
        return SubString(curr_cord->Left(), lower_idx, upper_idx);
    }
    if (lower_idx >= curr_cord->Left()->Length()) {     // all at right
        return SubString(curr_cord->Right(), lower_idx - curr_cord->Left()->Length(), upper_idx - curr_cord->Left()->Length());
    }
    SharedPointer<Cord> left = SubString(curr_cord->Left(), lower_idx, curr_cord->Left()->Length());
    SharedPointer<Cord> right = SubString(curr_cord->Right(), 0, upper_idx - curr_cord->Left()->Length());
    return ConcatCords(left, right);
}