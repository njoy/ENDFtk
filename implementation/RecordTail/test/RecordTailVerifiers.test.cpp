#include "catch.hpp"

#include "ENDFtk/implementation/RecordTail.hpp"

using namespace ENDFtk::implementation;

extern std::unique_ptr<RecordTail> myTail;
extern int mat;
extern int mf;
extern int mt;

SCENARIO( "Verifying the given numbers in the RecordTail" ){
  GIVEN( "correct tail numbers" ){
    THEN( "the numbers are verified without throwing an exception" ){
      REQUIRE_NOTHROW(MAT<RecordTail>(mat, mat, mf, mt));
      REQUIRE_NOTHROW(MF<RecordTail>(mf, mat, mf, mt));
      REQUIRE_NOTHROW(MT<RecordTail>(mt, mat, mf, mt));

      REQUIRE_NOTHROW(MAT<MF<RecordTail> >(mat, mf, mat, mf, mt));
      REQUIRE_NOTHROW(MAT< MF< MT< RecordTail>>>( mat, mf, mt, mat, mf, mt ));

//    TailVerifier<MAT, MF, MT>::type foo(mat, mf, mt, mat, mf, mt);
//    using SEND = TailVerifier<MAT, MF, MT>::type;
//    SEND send(mat, mf, 0, mat, mf, mt);
    }
  } // GIVEN
  GIVEN( "incorrect tail numbers" ){
    THEN( "exceptions are thrown" ){
      REQUIRE_THROWS(MAT<RecordTail>(0, mat, mf, mt));
      REQUIRE_THROWS(MF<RecordTail>(0, mat, mf, mt));
      REQUIRE_THROWS(MT<RecordTail>(0, mat, mf, mt));

      REQUIRE_THROWS(MAT< MF<RecordTail> >(0, 0, mat, mf, mt));
      REQUIRE_THROWS(MAT< MF< MT< RecordTail>>>( 0, 0, 0, mat, mf, mt ));
    }
  } // GIVEN
} // SCENARIO

