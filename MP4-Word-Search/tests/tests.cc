// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
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

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }


/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Horizental valid-1") {
    std::vector<std::vector<char>> puzzle{{'t', 'e', 't', 'o', 'r'},
                                          {'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation res = wss.FindWord("tetor");
    REQUIRE(res.word == "tetor");
    REQUIRE(res.char_positions[0].character == 't');
    REQUIRE(res.char_positions[0].row == 0);
    REQUIRE(res.char_positions[0].col == 0);
    REQUIRE(res.char_positions[1].character == 'e');
    REQUIRE(res.char_positions[1].row == 0);
    REQUIRE(res.char_positions[1].col == 1);
    REQUIRE(res.char_positions[2].character == 't');
    REQUIRE(res.char_positions[2].row == 0);
    REQUIRE(res.char_positions[2].col == 2);
    REQUIRE(res.char_positions[3].character == 'o');
    REQUIRE(res.char_positions[3].row == 0);
    REQUIRE(res.char_positions[3].col == 3);
    REQUIRE(res.char_positions[4].character == 'r');
    REQUIRE(res.char_positions[4].row == 0);
    REQUIRE(res.char_positions[4].col == 4);

    WordLocation res1 = wss.FindWord("tetor", CheckDirection::kHorizontal);
    REQUIRE(res1.word == "tetor");
    REQUIRE(res1.char_positions[0].character == 't');
    REQUIRE(res1.char_positions[0].row == 0);
    REQUIRE(res1.char_positions[0].col == 0);
    REQUIRE(res1.char_positions[1].character == 'e');
    REQUIRE(res1.char_positions[1].row == 0);
    REQUIRE(res1.char_positions[1].col == 1);
    REQUIRE(res1.char_positions[2].character == 't');
    REQUIRE(res1.char_positions[2].row == 0);
    REQUIRE(res1.char_positions[2].col == 2);
    REQUIRE(res1.char_positions[3].character == 'o');
    REQUIRE(res1.char_positions[3].row == 0);
    REQUIRE(res1.char_positions[3].col == 3);
    REQUIRE(res1.char_positions[4].character == 'r');
    REQUIRE(res1.char_positions[4].row == 0);
    REQUIRE(res1.char_positions[4].col == 4);
}

TEST_CASE("Horizental valid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'u'},
                                          {'t', 'e', 't', 'o', 'r'}};
    WordSearchSolver wss(puzzle);
    WordLocation res = wss.FindWord("tetor");
    REQUIRE(res.word == "tetor");
    REQUIRE(res.char_positions[0].character == 't');
    REQUIRE(res.char_positions[0].row == 2);
    REQUIRE(res.char_positions[0].col == 0);
    REQUIRE(res.char_positions[1].character == 'e');
    REQUIRE(res.char_positions[1].row == 2);
    REQUIRE(res.char_positions[1].col == 1);
    REQUIRE(res.char_positions[2].character == 't');
    REQUIRE(res.char_positions[2].row == 2);
    REQUIRE(res.char_positions[2].col == 2);
    REQUIRE(res.char_positions[3].character == 'o');
    REQUIRE(res.char_positions[3].row == 2);
    REQUIRE(res.char_positions[3].col == 3);
    REQUIRE(res.char_positions[4].character == 'r');
    REQUIRE(res.char_positions[4].row == 2);
    REQUIRE(res.char_positions[4].col == 4);

    WordLocation res1 = wss.FindWord("tetor", CheckDirection::kHorizontal);
    REQUIRE(res1.word == "tetor");
    REQUIRE(res1.char_positions[0].character == 't');
    REQUIRE(res1.char_positions[0].row == 2);
    REQUIRE(res1.char_positions[0].col == 0);
    REQUIRE(res1.char_positions[1].character == 'e');
    REQUIRE(res1.char_positions[1].row == 2);
    REQUIRE(res1.char_positions[1].col == 1);
    REQUIRE(res1.char_positions[2].character == 't');
    REQUIRE(res1.char_positions[2].row == 2);
    REQUIRE(res1.char_positions[2].col == 2);
    REQUIRE(res1.char_positions[3].character == 'o');
    REQUIRE(res1.char_positions[3].row == 2);
    REQUIRE(res1.char_positions[3].col == 3);
    REQUIRE(res1.char_positions[4].character == 'r');
    REQUIRE(res1.char_positions[4].row == 2);
    REQUIRE(res1.char_positions[4].col == 4);
}

TEST_CASE("Horizental invalid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("djfkre");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("djfkre", CheckDirection::kHorizontal);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("Horizental invalid-2") {
    std::vector<std::vector<char>> puzzle{{'t', 'e', 't', 'o', 'r'},
                                          {'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("", CheckDirection::kHorizontal);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("Vertical valid-1") {
    std::vector<std::vector<char>> puzzle{{'q', 'e', 'a', 'o', 'l'},
                                          {'s', 'e', 't', 'o', 'r'},
                                          {'x', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation res = wss.FindWord("qsx");
    REQUIRE(res.word == "qsx");
    REQUIRE(res.char_positions[0].character == 'q');
    REQUIRE(res.char_positions[0].row == 0);
    REQUIRE(res.char_positions[0].col == 0);
    REQUIRE(res.char_positions[1].character == 's');
    REQUIRE(res.char_positions[1].row == 1);
    REQUIRE(res.char_positions[1].col == 0);
    REQUIRE(res.char_positions[2].character == 'x');
    REQUIRE(res.char_positions[2].row == 2);
    REQUIRE(res.char_positions[2].col == 0);

    WordLocation res1 = wss.FindWord("qsx", CheckDirection::kVertical);
    REQUIRE(res1.word == "qsx");
    REQUIRE(res1.char_positions[0].character == 'q');
    REQUIRE(res1.char_positions[0].row == 0);
    REQUIRE(res1.char_positions[0].col == 0);
    REQUIRE(res1.char_positions[1].character == 's');
    REQUIRE(res1.char_positions[1].row == 1);
    REQUIRE(res1.char_positions[1].col == 0);
    REQUIRE(res1.char_positions[2].character == 'x');
    REQUIRE(res1.char_positions[2].row == 2);
    REQUIRE(res1.char_positions[2].col == 0);
}

TEST_CASE("Vertical valid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'g'},
                                          {'t', 'e', 't', 'o', 't'},
                                          {'t', 'e', 't', 'o', 'f'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("gtf");
    REQUIRE(result.word == "gtf");
    REQUIRE(result.char_positions[0].character == 'g');
    REQUIRE(result.char_positions[0].row == 0);
    REQUIRE(result.char_positions[0].col == 4);
    REQUIRE(result.char_positions[1].character == 't');
    REQUIRE(result.char_positions[1].row == 1);
    REQUIRE(result.char_positions[1].col == 4);
    REQUIRE(result.char_positions[2].character == 'f');
    REQUIRE(result.char_positions[2].row == 2);
    REQUIRE(result.char_positions[2].col == 4);

    WordLocation result1 = wss.FindWord("gtf", CheckDirection::kVertical);
    REQUIRE(result1.word == "gtf");
    REQUIRE(result1.char_positions[0].character == 'g');
    REQUIRE(result1.char_positions[0].row == 0);
    REQUIRE(result1.char_positions[0].col == 4);
    REQUIRE(result1.char_positions[1].character == 't');
    REQUIRE(result1.char_positions[1].row == 1);
    REQUIRE(result1.char_positions[1].col == 4);
    REQUIRE(result1.char_positions[2].character == 'f');
    REQUIRE(result1.char_positions[2].row == 2);
    REQUIRE(result1.char_positions[2].col == 4);
}

TEST_CASE("Vertical invalid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("gtfr");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("gtfe", CheckDirection::kVertical);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("Vertical invalid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("", CheckDirection::kVertical);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}
TEST_CASE("RightDia valid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("det");
    REQUIRE(result.word == "det");
    REQUIRE(result.char_positions[0].character == 'd');
    REQUIRE(result.char_positions[0].row == 0);
    REQUIRE(result.char_positions[0].col == 0);
    REQUIRE(result.char_positions[1].character == 'e');
    REQUIRE(result.char_positions[1].row == 1);
    REQUIRE(result.char_positions[1].col == 1);
    REQUIRE(result.char_positions[2].character == 't');
    REQUIRE(result.char_positions[2].row == 2);
    REQUIRE(result.char_positions[2].col == 2);

    WordLocation result1 = wss.FindWord("det", CheckDirection::kRightDiag);
    REQUIRE(result1.word == "det");
    REQUIRE(result1.char_positions[0].character == 'd');
    REQUIRE(result1.char_positions[0].row == 0);
    REQUIRE(result1.char_positions[0].col == 0);
    REQUIRE(result1.char_positions[1].character == 'e');
    REQUIRE(result1.char_positions[1].row == 1);
    REQUIRE(result1.char_positions[1].col == 1);
    REQUIRE(result1.char_positions[2].character == 't');
    REQUIRE(result1.char_positions[2].row == 2);
    REQUIRE(result1.char_positions[2].col == 2);
}

TEST_CASE("RightDia valid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("det");
    REQUIRE(result.word == "det");
    REQUIRE(result.char_positions[0].character == 'd');
    REQUIRE(result.char_positions[0].row == 0);
    REQUIRE(result.char_positions[0].col == 0);
    REQUIRE(result.char_positions[1].character == 'e');
    REQUIRE(result.char_positions[1].row == 1);
    REQUIRE(result.char_positions[1].col == 1);
    REQUIRE(result.char_positions[2].character == 't');
    REQUIRE(result.char_positions[2].row == 2);
    REQUIRE(result.char_positions[2].col == 2);

    WordLocation result1 = wss.FindWord("det", CheckDirection::kRightDiag);
    REQUIRE(result1.word == "det");
    REQUIRE(result1.char_positions[0].character == 'd');
    REQUIRE(result1.char_positions[0].row == 0);
    REQUIRE(result1.char_positions[0].col == 0);
    REQUIRE(result1.char_positions[1].character == 'e');
    REQUIRE(result1.char_positions[1].row == 1);
    REQUIRE(result1.char_positions[1].col == 1);
    REQUIRE(result1.char_positions[2].character == 't');
    REQUIRE(result1.char_positions[2].row == 2);
    REQUIRE(result1.char_positions[2].col == 2);
}

TEST_CASE("RightDia invalid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("dett");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("dett", CheckDirection::kRightDiag);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("RightDia invalid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a'},
                                          {'t', 'e', 't'},
                                          {'t', 'e', 't'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("dett");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("dett", CheckDirection::kRightDiag);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("RightDia invalid-3") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a'},
                                          {'t', 'e', 't'},
                                          {'t', 'e', 't'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("", CheckDirection::kRightDiag);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("LeftDia valid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("lot");
    REQUIRE(result.word == "lot");
    REQUIRE(result.char_positions[0].character == 'l');
    REQUIRE(result.char_positions[0].row == 0);
    REQUIRE(result.char_positions[0].col == 4);
    REQUIRE(result.char_positions[1].character == 'o');
    REQUIRE(result.char_positions[1].row == 1);
    REQUIRE(result.char_positions[1].col == 3);
    REQUIRE(result.char_positions[2].character == 't');
    REQUIRE(result.char_positions[2].row == 2);
    REQUIRE(result.char_positions[2].col == 2);

    WordLocation result1 = wss.FindWord("lot", CheckDirection::kLeftDiag);
    REQUIRE(result1.word == "lot");
    REQUIRE(result1.char_positions[0].character == 'l');
    REQUIRE(result1.char_positions[0].row == 0);
    REQUIRE(result1.char_positions[0].col == 4);
    REQUIRE(result1.char_positions[1].character == 'o');
    REQUIRE(result1.char_positions[1].row == 1);
    REQUIRE(result1.char_positions[1].col == 3);
    REQUIRE(result1.char_positions[2].character == 't');
    REQUIRE(result1.char_positions[2].row == 2);
    REQUIRE(result1.char_positions[2].col == 2);
}

TEST_CASE("LeftDia valid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("aet");
    REQUIRE(result.word == "aet");
    REQUIRE(result.char_positions[0].character == 'a');
    REQUIRE(result.char_positions[0].row == 0);
    REQUIRE(result.char_positions[0].col == 2);
    REQUIRE(result.char_positions[1].character == 'e');
    REQUIRE(result.char_positions[1].row == 1);
    REQUIRE(result.char_positions[1].col == 1);
    REQUIRE(result.char_positions[2].character == 't');
    REQUIRE(result.char_positions[2].row == 2);
    REQUIRE(result.char_positions[2].col == 0);

    WordLocation result1 = wss.FindWord("aet", CheckDirection::kLeftDiag);
    REQUIRE(result1.word == "aet");
    REQUIRE(result1.char_positions[0].character == 'a');
    REQUIRE(result1.char_positions[0].row == 0);
    REQUIRE(result1.char_positions[0].col == 2);
    REQUIRE(result1.char_positions[1].character == 'e');
    REQUIRE(result1.char_positions[1].row == 1);
    REQUIRE(result1.char_positions[1].col == 1);
    REQUIRE(result1.char_positions[2].character == 't');
    REQUIRE(result1.char_positions[2].row == 2);
    REQUIRE(result1.char_positions[2].col == 0);
}

TEST_CASE("LeftDia invalid-1") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'l'},
                                          {'t', 'e', 't', 'o', 'r'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("aegt");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("aegt", CheckDirection::kLeftDiag);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}

TEST_CASE("LeftDia invalid-2") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'n'},
                                          {'t', 'e', 't'},
                                          {'t', 'e', 't'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("nett");
    REQUIRE(result.word.empty());
    REQUIRE(result.char_positions.empty());

    WordLocation result1 = wss.FindWord("nett", CheckDirection::kLeftDiag);
    REQUIRE(result1.word.empty());
    REQUIRE(result1.char_positions.empty());
}