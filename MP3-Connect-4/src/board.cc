#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  //b.board[0][0] = DiskType::kEmpty;
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    for (unsigned int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

bool BoardLocationInBounds(int row, int col) {
  return row < Board::kBoardHeight && col < Board::kBoardWidth && row >= 0 && col >= 0;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("Invalid Column");
  } 
  for (unsigned int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    } 
    if (i == Board::kBoardHeight - 1) {
      throw std::runtime_error("Over the top");
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) || SearchForWinner(b, disk, WinningDirection::kVertical) 
    || SearchForWinner(b, disk, WinningDirection::kLeftDiag) || SearchForWinner(b, disk, WinningDirection::kRightDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  switch (to_check) {
    case WinningDirection::kHorizontal:
      return Horizontal(b, disk);
    case WinningDirection::kVertical: 
      return Vertical(b, disk);
    case WinningDirection::kLeftDiag:
      {
      int row[] = {0, 1, 2}; 
      for (unsigned int col = Board::kBoardWidth - 1; col > 2; --col) {
        if (b.board[row[0]][col] == disk && b.board[row[0] + 1][col - 1] == disk 
          && b.board[row[0] + 2][col - 2] == disk && b.board[row[0] + 3][col - 3] == disk) {
          return true;
        } 
        if (b.board[row[1]][col] == disk && b.board[row[1] + 1][col - 1] == disk 
          && b.board[row[1] + 2][col - 2] == disk && b.board[row[1] + 3][col - 3] == disk) {
          return true;
        }
        if (b.board[row[2]][col] == disk && b.board[row[2] + 1][col - 1] == disk 
          && b.board[row[2] + 2][col - 2] == disk && b.board[row[2] + 3][col - 3] == disk) {
          return true;
        }
      }
      return false;
      }
    case WinningDirection::kRightDiag:
      for (unsigned int row = 0; row <= Board::kBoardHeight - 4; ++row) {
        for (unsigned int col = 0; col <= Board::kBoardWidth - 4; ++col) {
          if (b.board[row][col] == disk && b.board[row + 1][col + 1] == disk 
            && b.board[row + 2][col + 2] == disk && b.board[row + 3][col + 3] == disk) {
              return true;
          }
        }
      }
      return false;
    default:
      return false;
  }
}
/**************************************************************************/
/* Winning Type (Horizontal && Vertical)                                  */
/**************************************************************************/
bool Horizontal(Board& b, DiskType disk) {
  for (unsigned int row = 0; row < Board::kBoardHeight; ++row) {
    for (unsigned int col = 0; col <= Board::kBoardWidth - 4; ++col) {
      if (b.board[row][col] == disk && b.board[row][col + 1] == disk 
          && b.board[row][col + 2] == disk && b.board[row][col + 3] == disk) {
            return true;
      }
    }
  }
  return false;
}

bool Vertical(Board& b, DiskType disk) {
  for (unsigned int col = 0; col < Board::kBoardWidth; ++col) {
    for (unsigned int row = 0; row <= Board::kBoardHeight - 4; ++row) {
      if (b.board[row][col] == disk && b.board[row + 1][col] == disk 
          && b.board[row + 2][col] == disk && b.board[row + 3][col] == disk) {
            return true;
      }
    }
  }
  return false;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}