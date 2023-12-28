#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>


class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

  bool BFSnoR(const int& start_vertex, std::set<int>& visited, int target) const;
  bool BFSwR(const int& start_vertex, std::set<int>& visited, int target, const std::string &relationship) const;
  
private:
  std::map<int, std::map<int, std::string>> graph_;
  void Group1(const int& start_vertex, std::set<int>& visited, size_t& num) const;
  void Group23(const int& start_vertex, std::set<int>& visited, size_t& num, const std::vector<std::string>& relationships) const;
  std::set<std::string> relationships_;
};

#endif
