// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/record/Tail.hpp"
#include "ENDFtk/record/TailVerifying.hpp"

// other includes
#include <functional>

// convenience typedefs
using namespace njoy::ENDFtk::record;

constexpr int mat = 125;
constexpr int mf = 4;
constexpr int mt = 2;

SCENARIO( "Checking the values of MAT, MF, and MT" ){
    GIVEN("A string containing the MAT, MF, and MT of a Record") {
        WHEN("Constructed from values") {
            auto myTail = std::make_unique< Tail >(mat, mf, mt);
            THEN("the correct values are read in") {
                CHECK(mat == myTail->material());
                CHECK(mf == myTail->file());
                CHECK(mt == myTail->section());
            }
        }
        auto lineNumber = 0l;
        WHEN("Constructed from a string") {
            std::string tail(" 125 4  2    1\n");
            auto it = tail.begin();
            auto end = tail.end();
            auto myTail = std::make_unique< Tail >(it, end, lineNumber);
            THEN("the correct values are read in") {
                CHECK(mat == myTail->material());
                CHECK(mf == myTail->file());
                CHECK(mt == myTail->section());
            }
        }
        WHEN("Constructed from a string without gaps") {
            std::string tail("01254422254321\n");
            auto it = tail.begin();
            auto end = tail.end();
            auto myTail = std::make_unique< Tail >(it, end, lineNumber);
            THEN("the correct values are read in") {
                CHECK(125 == myTail->material());
                CHECK(44 == myTail->file());
                CHECK(222 == myTail->section());
            }
        }
#if !(defined(_WIN32) && defined(_DEBUG))
        WHEN("Constructed from a stringwith incomplete NS") {
            std::string tail(" 125 4  2\n");
            auto it = tail.begin();
            auto end = tail.end();
            auto myTail = std::make_unique< Tail >(it, end, lineNumber);
            THEN("the correct values are read in") {
                CHECK(mat == myTail->material());
                CHECK(mf == myTail->file());
                CHECK(mt == myTail->section());
            }
        }
        WHEN("Constructed from a string with invalid NS") {
            std::string tail(" 125 4  2 a\n");
            auto it = tail.begin();
            auto end = tail.end();
            CHECK_THROWS(std::make_unique< Tail >(it, end, lineNumber));
        }
        WHEN("Constructed from a string with invalid MT") {
            std::string tail(" 125 4 a2\n");
            auto it = tail.begin();
            auto end = tail.end();
            CHECK_THROWS(std::make_unique< Tail >(it, end, lineNumber));
        }
        WHEN("Constructed from a string with invalid MF") {
            std::string tail(" 125a4  2\n");
            auto it = tail.begin();
            auto end = tail.end();
            CHECK_THROWS(std::make_unique< Tail >(it, end, lineNumber));
        }
        WHEN("Constructed from a string with invalid MAT") {
            std::string tail(" 1a5 4  2\n");
            auto it = tail.begin();
            auto end = tail.end();
            CHECK_THROWS(std::make_unique< Tail >(it, end, lineNumber));
        }

#endif
    }
} // SCENARIO

SCENARIO( "Verifying the given numbers in the RecordTail" ){
  /* Catch requirement macros do not like multi-argument templates.
   * These aliases provide a work around
   */
  using TailVerifyingMATMF = TailVerifying< MAT, MF >;
  using TailVerifyingMATMFMT = TailVerifying< MAT, MF, MT >;
  auto lineNumber = 0l;
  GIVEN( "correct tail numbers" ){
    std::string tail(" 125 4  2    1\n");
    THEN( "the numbers are verified without throwing an exception" ){
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_NOTHROW( TailVerifying< MAT >( mat, it, end, lineNumber ) );
    }
    THEN( "the numbers are verified without throwing an exception" ){
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_NOTHROW( TailVerifying< MF >( mf, it, end, lineNumber ) );
    }
    THEN( "the numbers are verified without throwing an exception" ){
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_NOTHROW( TailVerifying< MT >( mt, it, end, lineNumber ) );
    }
    THEN( "the numbers are verified without throwing an exception" ){
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_NOTHROW( TailVerifyingMATMF( mat, mf, it, end, lineNumber ) );
    }
    THEN( "the numbers are verified without throwing an exception" ){
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_NOTHROW( TailVerifyingMATMFMT( mat, mf, mt, it, end, lineNumber ) );
    }
  }
#if !(defined(_WIN32) && defined(_DEBUG))
  GIVEN( "incorrect tail numbers" ){
    std::string tail(" 125 4  2\n");
    auto end = tail.end();
    WHEN("Constructed from a string"){
      auto it = tail.begin();
      CHECK_THROWS( TailVerifying< MAT >( 0, it, end, lineNumber ) );
    }
    WHEN("Constructed from a string"){
      auto it = tail.begin();
      CHECK_THROWS( TailVerifying< MF >( 0, it, end, lineNumber ) );
    }
    WHEN("Constructed from a string"){
      auto it = tail.begin();
      CHECK_THROWS( TailVerifying< MT >( 0, it, end, lineNumber ) );
    }
    WHEN("Constructed from a string"){
      auto it = tail.begin();
      CHECK_THROWS( TailVerifyingMATMF( 0, 0, it, end, lineNumber ) );
    }
    WHEN("Constructed from a string"){
      auto it = tail.begin();
      CHECK_THROWS( TailVerifyingMATMFMT( 0, 0, 0, it, end, lineNumber ) );
    }
  }
#endif
}
