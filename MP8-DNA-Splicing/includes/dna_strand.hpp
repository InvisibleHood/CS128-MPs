#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;    
  DNAstrand(const DNAstrand& rhs) = delete;     
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();   

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  bool FindPattern(Node*& current, const char* pattern, unsigned int size_p);

  // void PushBack(char value);
  // friend std::ostream& operator<<(std::ostream& os, const DNAstrand& dna);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif