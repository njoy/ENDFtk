SCENARIO( "Checking the values of MAT, MF, and MT" ){
  GIVEN( "A string containing the MAT, MF, and MT of a Record" ){
    WHEN("Constructed from values"){
      auto myTail = std::make_unique< Tail >( mat, mf, mt );
      THEN( "the correct values are read in" ){
        CHECK( mat == myTail->material() );
        CHECK(  mf == myTail->file()  );
        CHECK(  mt == myTail->section()  );
      }
    }
    auto lineNumber = 0l;
    WHEN("Constructed from a string"){
      std::string tail(" 125 4  2    1\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        CHECK( mat == myTail->material() );
        CHECK(  mf == myTail->file()  );
        CHECK(  mt == myTail->section()  );
      }
    }
    WHEN("Constructed from a string without gaps"){
      std::string tail("01254422254321\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        CHECK( 125 == myTail->material() );
        CHECK(  44 == myTail->file()  );
        CHECK( 222 == myTail->section()  );
      }
    }
    WHEN("Constructed from a stringwith incomplete NS"){
      std::string tail(" 125 4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      auto myTail = std::make_unique< Tail >( it, end, lineNumber );
      THEN( "the correct values are read in" ){
        CHECK( mat == myTail->material() );
        CHECK(  mf == myTail->file()  );
        CHECK(  mt == myTail->section()  );
      }
    }
    WHEN("Constructed from a string with invalid NS"){
      std::string tail(" 125 4  2 a\n");
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MT"){
      std::string tail(" 125 4 a2\n");
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MF"){
      std::string tail(" 125a4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
    WHEN("Constructed from a string with invalid MAT"){
      std::string tail(" 1a5 4  2\n");
      auto it = tail.begin();
      auto end = tail.end();
      CHECK_THROWS( std::make_unique< Tail >( it, end, lineNumber ) );
    }
  }
} // SCENARIO
