#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

constexpr int mat = 125;
constexpr int mf = 4;
constexpr int mt = 2;

SCENARIO( "Checking the values of MAT, MF, and MT" ){
  GIVEN( "A string containing the MAT, MF, and MT of a Record" ){
    WHEN("Constructed from values"){
      auto myTail = std::make_unique< Tail >( mat, mf, mt );
      THEN( "the correct values are read in" ){
        REQUIRE( mat == myTail->material() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  mt == myTail->section()  );
      }
    }
    auto lineNumber = 0l;
    WHEN("Constructed from a string"){
      std::string tail(" 125 4  2    1\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        REQUIRE( mat == myTail->material() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  mt == myTail->section()  );
      }
    }
    WHEN("Constructed from a string without gaps"){
      std::string tail("01254422254321\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        REQUIRE( 125 == myTail->material() );
        REQUIRE(  44 == myTail->file()  );
        REQUIRE( 222 == myTail->section()  );
      }
    }
    WHEN("Constructed from a stringwith incomplete NS"){
      std::string tail(" 125 4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        REQUIRE( mat == myTail->material() );
        REQUIRE(  mf == myTail->file()  );
        REQUIRE(  mt == myTail->section()  );
      }
    }
    WHEN("Constructed from a string with invalid NS"){
      std::string tail(" 125 4  2 a\n");
      auto it = tail.begin();
      auto end = tail.end();
      REQUIRE_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MT"){
      std::string tail(" 125 4 a2\n");
      auto it = tail.begin();
      auto end = tail.end();
      REQUIRE_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MF"){
      std::string tail(" 125a4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      REQUIRE_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MAT"){
      std::string tail(" 1a5 4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      REQUIRE_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
  }
} // SCENARIO
