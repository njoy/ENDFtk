#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/gendf/SectionBase.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

// trivial class to access protected constructors
class TestBase : public gendf::SectionBase {
public:
  TestBase( double ZA, double AWR, int MT,
            int NL, int NZ, int LRFLAG, int NGN ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN ) {};
  TestBase( const HEAD& head ) :
    SectionBase( head ) {};
};

// forward declarations
std::string chunk();
void verifySection( TestBase );

// tests
SCENARIO( "BaseSection tests") {

  GIVEN( "a string representing the Section" ) {

    std::string line = chunk();
    auto begin = line.begin();
    auto end = line.end();
    long lineNumber = 0;
    auto head = StructureDivision( begin, end, lineNumber );

    THEN( "the section can be constructed" ) {

      TestBase section(asHead(head));

      AND_THEN( "we can get the parameters from it" ) {
        verifySection( section );
      } // AND_THEN
    } // THEN
  } // GIVEN

  WHEN( "the section is created from parameters" ) {

    THEN( "the section can be constructed" ) {

      TestBase section( 92235., 0.0, 1, 2, 1, 0, 5 );

      AND_THEN( "we can get the parameters from it" ) {
        verifySection( section );
      } // AND_THEN
    } // THEN
  } // WHEN

} // SCENARIO

std::string chunk(){

  return
    " 9.223500+4 0.000000+0          2          1          0          59228 3  1    1\n";
}

void verifySection( TestBase section ) {
  REQUIRE( 1 == section.MT() );
  REQUIRE( 1 == section.sectionNumber() );
  REQUIRE( 92235 == section.ZA() );
  REQUIRE( 0.0 == section.atomicWeightRatio() );
  REQUIRE( 0.0 == section.AWR() );
  REQUIRE( 2 == section.NL() );
  REQUIRE( 2 == section.numLegendre() );
  REQUIRE( 1 == section.legendreOrder() );
  REQUIRE( 1 == section.NZ() );
  REQUIRE( 1 == section.numDilutions() );
  REQUIRE( 0 == section.LRFLAG() );
  REQUIRE( 0 == section.complexBreakUp() );
  REQUIRE( 5 == section.NGN() );
  REQUIRE( 5 == section.numGroups() );
}
