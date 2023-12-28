#include "WordSearchSolver.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cstddef>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation hor = FindWord(word, CheckDirection::kHorizontal);
  WordLocation ver = FindWord(word, CheckDirection::kVertical);
  WordLocation right_d = FindWord(word, CheckDirection::kRightDiag);
  WordLocation left_d = FindWord(word, CheckDirection::kLeftDiag);
  if (!hor.word.empty()) {
    return hor;
  } 
  if (!ver.word.empty()) {
    return ver;
  } 
  if (!right_d.word.empty()) {
    return right_d;
  }
  if (!left_d.word.empty()) {
    return left_d;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  switch (direction) {
    case CheckDirection::kHorizontal:
      return Horizontal(word);
    case CheckDirection::kVertical:
      return Vertical(word);
    case CheckDirection::kRightDiag:
      return RightDiag(word);
    case CheckDirection::kLeftDiag:
      return LeftDiag(word);
  } 
  return WordLocation{};
}

WordLocation WordSearchSolver::Horizontal(const std::string& word) {
  size_t len = word.size();
  if (len <= 0 || len > puzzle_width_) {
    return WordLocation{};
  }
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      if (puzzle_.at(i).at(j) == (word.at(0)) && (j + len) <= puzzle_width_) {
        size_t temp_col = j;
        WordLocation wlc;
        size_t wd_idx = 0;
        while (wd_idx < word.size()) {
          if (puzzle_.at(i).at(temp_col) != (word.at(wd_idx))) {break;}
          wlc.char_positions.push_back(CharPositions{word.at(wd_idx), i, temp_col});
          wlc.word += word.at(wd_idx);
          temp_col++;
          wd_idx++;
        }
        if (wlc.word == word) {
          return wlc;
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::Vertical(const std::string& word) {
  size_t len = word.size();
  if (len <= 0 || len > puzzle_height_) {
    return WordLocation{};
  }
  for (size_t i = 0; i < puzzle_width_; ++i) {
    WordLocation wlc;
    for (size_t j = 0; j <= puzzle_height_ - len; ++j) {
      for (size_t k = 0; k < word.size(); ++k) {
        if (puzzle_.at(j + k).at(i) != word.at(k)) {
          wlc.char_positions.clear();
          break;
        }
        wlc.char_positions.push_back(CharPositions{word.at(k), j + k, i});
        if (wlc.char_positions.size() == word.size()) {
          wlc.word = word;
          return wlc;
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::RightDiag(const std::string& word) {
  size_t len = word.size();
  if (len <= 0 || len > puzzle_height_ || len > puzzle_width_) {
    return WordLocation{};
  }
  for (size_t i = 0; i <= puzzle_height_ - len; ++i) {
    for (size_t j = 0; j <= puzzle_width_ - len; ++j) {
      WordLocation wlc;
      for (size_t k = 0; k < word.size(); k++) {
        if (puzzle_.at(i + k).at(j + k) != word.at(k)) {
          break;
        }
        wlc.char_positions.push_back(CharPositions{word.at(k), i + k, j + k});
        if (wlc.char_positions.size() == word.size()) {
          wlc.word = word;
          return wlc;
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::LeftDiag(const std::string& word) {
  size_t len = word.size();
  if (len <= 0 || len > puzzle_height_ || len > puzzle_width_) {
    return WordLocation{};
  }
  for (size_t i = 0; i <= puzzle_height_ - len; ++i) {
    for (size_t j = 0; j < puzzle_width_; ++j) {
      WordLocation wlc;
      for (size_t wd = 0; wd < word.size(); ++wd) {
        if (j < len - 1 || puzzle_.at(i + wd).at(j - wd) != word.at(wd)) {
          break;
        }
        wlc.char_positions.push_back(CharPositions{word.at(wd), i + wd, j - wd});
      }
      if (wlc.char_positions.size() == word.size()) {
          wlc.word = word;
          return wlc;
      }
    }
  }
  return WordLocation{};
}




