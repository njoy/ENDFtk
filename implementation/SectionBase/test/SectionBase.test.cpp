#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "SectionBase Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "SectionBase Complete!";
  return result;
}

using namespace ENDFtk::implementation;

SCENARIO( "SectionBase tests"){
  GIVEN( "a string represnting the Section" ){
    std::string line = 
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1\n";

    auto begin = line.begin();
    auto end = line.end();
    long lineNumber = 2;
    auto head = StructureDivision( begin, end, lineNumber );

    WHEN( "given good MAT, MF numbers"){
      int MAT = 125;
      int MF = 3;
      THEN( "the base can be constructed without throwing" ){
        std::unique_ptr<SectionBase> base;
          REQUIRE_NOTHROW(
            base = std::make_unique<SectionBase>( asHead(head), MAT, MF) );

        AND_THEN( "we can get the ZA, MT, and atomicWeightRatio" ){
          REQUIRE( 1 == base->MT() );
          REQUIRE( 1001 == base->ZA() );
          REQUIRE( 0.9991673 == base->atomicWeightRatio() );
        } // AND_THEN
      } // THEN
    } // WHEN

    WHEN( "given bad MAT and MF numbers" ){
      int MAT = 1;
      int MF = 1;
      THEN( "an exception is thrown on construction" ){
        REQUIRE_THROWS( SectionBase( asHead(head), MAT, MF ) );
        REQUIRE_THROWS( SectionBase( asHead(head), MAT, 3 ) );
        REQUIRE_THROWS( SectionBase( asHead(head), 125, MF ) );
      }
    }
  } // GIVEN
} // SCENARIO

