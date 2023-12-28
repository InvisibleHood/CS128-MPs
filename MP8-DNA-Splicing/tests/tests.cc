#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <iostream>
#include "dna_strand.hpp"


TEST_CASE("single occurance at the end", "se1m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('b');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('s');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "bbcshla");
    insert.PushBack('z');
    insert.PushBack('s');
    char d[] = "hla";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "bbcszs");
}

TEST_CASE("single occurance at the end2", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('b');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "bhlahla");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    insert.PushBack('a');
    insert.PushBack('a');
    char d[] = "hla\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "bhlazsvaa");
}

TEST_CASE("single occurance at the end3", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('b');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "bhlahla");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    insert.PushBack('a');
    insert.PushBack('a');
    char d[] = "a\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "bhlahlzsvaa");
}

TEST_CASE("one char at the end4", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('b');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    dna.PushBack('h');
    dna.PushBack('l');
    dna.PushBack('a');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "bhlahla");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    insert.PushBack('a');
    insert.PushBack('a');
    char d[] = "a\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "bhlahlzsvaa");
}

TEST_CASE("two chars at the end", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('e');
    dna.PushBack('f');
    dna.PushBack('g');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdefg");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    char d[] = "fg\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "abcdezsv");
}

TEST_CASE("whole sequence", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('e');
    dna.PushBack('f');
    dna.PushBack('g');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdefg");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    char d[] = "abcdefg\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "zsv");
}

TEST_CASE("single occurance at the end8", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('e');
    dna.PushBack('f');
    dna.PushBack('g');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdefg");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    char d[] = "abcdefg\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "zsv");
}

TEST_CASE("not found", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('e');
    dna.PushBack('f');
    dna.PushBack('g');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdefg");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    char d[] = "fgh\0";
    try {
        dna.SpliceIn(d, insert);
        REQUIRE(false);
    } catch(...) {
        REQUIRE(true);
    };
    // std::ostringstream oss2;
    // oss2 << dna;
}

TEST_CASE("replaced with one repetition", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdabcd");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    char d[] = "abcd\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "abcdzsvvvvv");
}

TEST_CASE("In the Middle", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('d');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcdabcd");
    insert.PushBack('z');
    insert.PushBack('s');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    insert.PushBack('v');
    char d[] = "bcdabc\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "azsvvvvvd");
}

TEST_CASE("single", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "a");
    insert.PushBack('z');
    char d[] = "a\0";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "z");
}

TEST_CASE("single abc at the end", "se2m") { 
    DNAstrand dna;
    DNAstrand insert;
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    dna.PushBack('a');
    dna.PushBack('a');
    dna.PushBack('b');
    dna.PushBack('c');
    std::ostringstream oss;
    oss << dna;
    REQUIRE(oss.str() == "abcaabc");
    insert.PushBack('z');
    insert.PushBack('s');
    char d[] = "abc";
    dna.SpliceIn(d, insert);
    std::ostringstream oss2;
    oss2 << dna;
    REQUIRE(oss2.str() == "abcazs");
}
