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

SCENARIO( "SectionBase tests"){
  GIVEN( "a string represnting the Section" ){
    std::string line = 
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1\n";

    auto begin = line.begin();
    auto end = line.end();
    long lineNumber = 2;
    auto head = ENDFtk::implementation::StructureDivision(
        begin, end, lineNumber);

    THEN( "we can get the ZA, MT, and atomicWeightRatio" ){
      ENDFtk::implementation::SectionBase base( asHead( head ) );
      REQUIRE( 1 == base.MT() );
      REQUIRE( 1001 == base.ZA() );
      REQUIRE( 0.9991673 == base.atomicWeightRatio() );

    } // THEN

  } // GIVEN
} // SCENARIO

