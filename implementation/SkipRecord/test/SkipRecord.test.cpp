#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "SkipRecord Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "SkipRecord Complete!";
  return result;
}

SCENARIO( "TextRecord Tests", "[ENDFtk], [TextRecord]" ){
  GIVEN( "a string rvalue" ){
  std::string line = 
    "General information for Version u235ib06ao17g6cnu5cf2             9228 1451   12\n";

  THEN( "the constructor works" ){
    auto it = line.begin();
    auto end = line.end();
    long lineNumber = 12;
    ENDFtk::implementation::SkipRecord skip( it, end, lineNumber );

    REQUIRE( 9228 == skip.MAT() );
    REQUIRE( 1    == skip.MF() );
    REQUIRE( 451  == skip.MT() );

    }
  } // GIVEN
} // SCENARIO

