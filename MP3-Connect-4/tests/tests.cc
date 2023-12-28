// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[kBoardHeight][kBoardWidth],
              DiskType student[kBoardHeight][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

void CopyBoard(DiskType sol[][kBoardWidth], DiskType stu[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      stu[i][j] = sol[i][j];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}


TEST_CASE("Dropping a disk at valid columns", "[board_drop]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  Board student;  // NOLINT
  InitBoard(student);

  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 7), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 7), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -1), std::runtime_error);

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[0][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[1][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[2][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[3][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[4][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board)); 

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[5][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 0), std::runtime_error);
}

TEST_CASE("Board location in bounds", "[board_location]") {
  REQUIRE(BoardLocationInBounds(0, 0) == true);
  REQUIRE(BoardLocationInBounds(0, 1) == true);
  REQUIRE(BoardLocationInBounds(0, 2) == true);
  REQUIRE(BoardLocationInBounds(0, 3) == true);
  REQUIRE(BoardLocationInBounds(0, 4) == true);
  REQUIRE(BoardLocationInBounds(0, 5) == true);
  REQUIRE(BoardLocationInBounds(0, 6) == true);
  REQUIRE(BoardLocationInBounds(-1, -1) == false);
  REQUIRE(BoardLocationInBounds(-1, 7) == false);
  REQUIRE(BoardLocationInBounds(6, -1) == false);
  REQUIRE(BoardLocationInBounds(6, 7) == false);
  REQUIRE_FALSE(BoardLocationInBounds(6, -7));
  REQUIRE_FALSE(BoardLocationInBounds(21, 33));
  REQUIRE_FALSE(BoardLocationInBounds(-5, -9));
  REQUIRE_FALSE(BoardLocationInBounds(-2, 13));
}



TEST_CASE("Dropping a disk Edge Cases / over the top", "[board_drop_edge_case]") {
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  Board student; 
  InitBoard(student);

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer1, 0));
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer2, 0));
  solution[1][0] = DiskType::kPlayer2;
  REQUIRE(AreEqual(solution, student.board));

  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kEmpty, 0));
  REQUIRE(AreEqual(solution, student.board));

  
  DiskType solution1[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  
  REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kEmpty, 0));
  REQUIRE(AreEqual(solution1, student.board));

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  solution1[5][0] = DiskType::kPlayer1;
  REQUIRE(AreEqual(solution1, student.board));

  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 0), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 0), std::runtime_error);
}




TEST_CASE("Check for winner in horizontal", "[board_horizontal_winner]") {
  
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
}


TEST_CASE("Search for winner in horizontal", "[board_horizontal_winner]") {
  /*
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
  */
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);
  //REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  
}

TEST_CASE("Search for winner in all four cases", "[board_winner]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };
  
  Board student1;  // NOLINT
  InitBoard(student1);
  DropDiskToBoard(student1, DiskType::kPlayer1, 3);
  DropDiskToBoard(student1, DiskType::kPlayer2, 3);
  DropDiskToBoard(student1, DiskType::kPlayer1, 4);
  DropDiskToBoard(student1, DiskType::kPlayer2, 4);
  DropDiskToBoard(student1, DiskType::kPlayer1, 5);
  DropDiskToBoard(student1, DiskType::kPlayer2, 5);
  DropDiskToBoard(student1, DiskType::kPlayer1, 6);
  REQUIRE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);

  solution[0][5] = DiskType::kPlayer2;
  CopyBoard(solution, student1.board);
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kHorizontal));

  
  //vertical:
  DiskType solution1[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };

  CopyBoard(solution1, student1.board);
  REQUIRE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kVertical) == true);

  solution1[5][0] = DiskType::kEmpty;
  CopyBoard(solution1, student1.board);
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kVertical));

  //leftDiag
  DiskType solution2[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  CopyBoard(solution2, student1.board);
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(student1,DiskType::kPlayer1,WinningDirection::kLeftDiag));

  solution2[5][0] = DiskType::kPlayer2;
  CopyBoard(solution2, student1.board);
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  DiskType sol[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  CopyBoard(sol, student1.board);
  REQUIRE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kHorizontal));      
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kVertical));



  //RightDiag
  DiskType solution3[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1,DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2,DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2,DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };

  CopyBoard(solution3, student1.board);
  REQUIRE(SearchForWinner(student1,DiskType::kPlayer1,WinningDirection::kRightDiag));

  solution3[0][0] = DiskType::kEmpty;
  CopyBoard(solution3, student1.board);
  REQUIRE_FALSE(SearchForWinner(student1,DiskType::kPlayer1,WinningDirection::kRightDiag));

  DiskType sol1[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}
  };

  CopyBoard(sol1, student1.board);
  REQUIRE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kHorizontal));      
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student1, DiskType::kPlayer2, WinningDirection::kLeftDiag));


}


TEST_CASE("No winner at ALL", "TIE") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 2), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 4), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 5), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 6), std::runtime_error);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag) == false);
}

/////////////////////////////////////////////////////////////////////////////////////////////