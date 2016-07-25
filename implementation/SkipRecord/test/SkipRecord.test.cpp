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

SCENARIO( "SkipRecord Tests", "[ENDFtk], [SkipRecord]" ){
  GIVEN( "a string rvalue" ){
    std::string line = 
      "General information for Version u235ib06ao17g6cnu5cf2             ";
    std::string MAT = "9228";
    std::string MF = " 1";
    std::string MT = "451";
    std::string NS = "   12\n";

    WHEN( "the MAT, MF, MT numbers are valid (i.e., > 0)" ){
      line += MAT + MF + MT + NS;

      THEN( "the constructor works" ){
        auto it = line.begin();
        auto end = line.end();
        long lineNumber = 12;
        REQUIRE_NOTHROW( ENDFtk::implementation::SkipRecord skip( it, end, lineNumber) );


      }
    } // WHEN

//  WHEN( "the MAT number is negative" ){
//    MAT = "-928";
//    MF  = "-1";
//    MT  = "  0";
//    line += MAT + MF + MT + NS;
//    auto it = line.begin();
//    auto end = line.end();
//    long lineNumber = 12;

//    THEN( "the constructor throws" ){
//      REQUIRE_THROWS(ENDFtk::implementation::SkipRecord skip( 
//              it, end, lineNumber) );
//    }
//  }
  } // GIVEN
} // SCENARIO

