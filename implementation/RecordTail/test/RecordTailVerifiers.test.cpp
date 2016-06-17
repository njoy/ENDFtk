#include "catch.hpp"

#include "ENDFtk/implementation/RecordTail.hpp"

using namespace ENDFtk::implementation;

extern std::unique_ptr<RecordTail> myTail;
extern int mat;
extern int mf;
extern int mt;

SCENARIO( "Verifying the given numbers in the RecordTail" ){
  /* Catch requirement macros do not like multi-argument templates.
   * These aliases provide a work around 
   */
  using TailVerifyingMATMF = TailVerifying< MAT, MF >;
  using TailVerifyingMATMFMT = TailVerifying< MAT, MF, MT >;
  GIVEN( "correct tail numbers" ){
    THEN( "the numbers are verified without throwing an exception" ){
      REQUIRE_NOTHROW( TailVerifying< MAT >( mat, mat, mf, mt ) );
      REQUIRE_NOTHROW( TailVerifying< MF >( mf, mat, mf, mt ) );
      REQUIRE_NOTHROW( TailVerifying< MT >( mt, mat, mf, mt ) );
      REQUIRE_NOTHROW( TailVerifyingMATMF( mat, mf, mat, mf, mt ) );
      REQUIRE_NOTHROW( TailVerifyingMATMFMT( mat, mf, mt, mat, mf, mt ) );
      
    }
  }
  GIVEN( "incorrect tail numbers" ){
    THEN( "exceptions are thrown" ){
      REQUIRE_THROWS( TailVerifying< MAT >( 0, mat, mf, mt ) );
      REQUIRE_THROWS( TailVerifying< MF >( 0, mat, mf, mt ) );
      REQUIRE_THROWS( TailVerifying< MT >( 0, mat, mf, mt ) );
      REQUIRE_THROWS( TailVerifyingMATMF( 0, 0, mat, mf, mt ) );
      REQUIRE_THROWS( TailVerifyingMATMFMT( 0, 0, 0, mat, mf, mt ) );
    }
  }
}

