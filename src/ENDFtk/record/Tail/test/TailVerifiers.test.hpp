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
}
