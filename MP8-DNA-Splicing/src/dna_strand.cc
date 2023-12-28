#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
    while(head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (pattern == nullptr || to_splice_in.head_ == nullptr || &to_splice_in == this || pattern[0] == '\0') {return;}
    unsigned int size_p = 0;
    while (pattern[size_p] != '\0') {size_p++;}
    Node* current = head_; bool find = false; Node* base = nullptr; Node* tbase = nullptr; Node* end = nullptr;
    while (current != nullptr) {
        if (current->data == pattern[0]) {
            base = current;
            if (FindPattern(current, pattern, size_p)) {
                tbase = base;
                end = current;
                find = true;
                continue;
            }
        }
        current = current->next;
    }
    if (!find) {throw std::invalid_argument("NO PATTERN");}
    current = head_;
    if (head_ == tbase) {
        while(tbase != end) {
            tbase = head_->next;
            delete head_;
            head_ = tbase;
        }
        head_ = to_splice_in.head_;
    } else {
        if (tail_->next == end) {tail_ = to_splice_in.tail_;}
        while (current->next != tbase) {current = current->next;}
        Node* stop = tbase;
        while (tbase != end) {
            stop = tbase->next;
            delete tbase;
            tbase = stop;
        }
        current->next = to_splice_in.head_;
    }
    to_splice_in.tail_->next = end;
    to_splice_in.head_ = nullptr;to_splice_in.tail_ = nullptr;
}

bool DNAstrand::FindPattern(Node*& current, const char* pattern, unsigned int size_p) {
    Node* now = current;
    for (unsigned int i = 0; i < size_p; i++) {
        if (current == nullptr || current->data != pattern[i]) {
            current = now;
            return false;
        }
        current = current->next;
    }
    return true;
}


// unsigned pidx = 0;Node* current = head_;Node* end = nullptr;Node* base = nullptr;Node* tbase = nullptr;
    // while (current != nullptr) {
    //     if (current->data == pattern[pidx]) {
    //         if (pidx == 0) {base = current;}
    //         pidx++;
    //         if (pidx == size_p) {
    //             tbase = base;
    //             end = current;
    //             pidx = 0;
    //         }
    //     } else {pidx = 0;}
    //     current = current->next;
    // }
    // if (tbase == nullptr || end == nullptr) {throw std::invalid_argument("NO PATTERN");}
    // // base = nullptr;
    // current = head_;
    // Node* stop = end->next;
    // if (head_ == tbase) {
    //     while (tbase != stop) {
    //         tbase = head_->next;
    //         delete head_;
    //         head_ = tbase;
    //     }
    //     head_ = to_splice_in.head_;
    // } else {
    //     if (tail_ == end) {tail_ = to_splice_in.tail_;}
    //     while (current->next != tbase) {current = current->next;}
    //     Node* d = tbase;
    //     while (d != stop) {
    //         d = tbase->next;
    //         delete tbase;
    //         tbase = d;
    //     }
    //     current->next = to_splice_in.head_;
    // }
    // to_splice_in.tail_->next = tbase;
    // tbase = nullptr;
    // end = nullptr;
    // current = nullptr;
    // to_splice_in.head_ = nullptr;to_splice_in.tail_ = nullptr;

//=========================================================
// void DNAstrand::PushBack(char value) {
//     if (head_ == nullptr) {
//         head_ = new Node (value);
//         tail_ = head_;
//     } else {
//         Node* last = new Node (value);
//         tail_->next = last;
//         tail_ = last;
//     }
// }

// std::ostream& operator<<(std::ostream& os, const DNAstrand& dna) {
//     Node* next = dna.head_;
//     while (next != nullptr) {
//         os << next->data;
//         next = next->next;
//     }
//     return os;
// }