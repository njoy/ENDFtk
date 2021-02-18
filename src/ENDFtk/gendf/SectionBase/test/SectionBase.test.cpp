#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/gendf/SectionBase.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using namespace njoy::ENDFtk::gendf;

// trivial class to access protected constructors
class TestBase : public SectionBase {
public:
  TestBase( double ZA, double AWR, int MT,
            int NL, int NZ, int LRFLAG, int NGN,
            std::vector< DataRecord > lists ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN, lists ) {};
  template< typename Iterator >
  TestBase( const HEAD& head, Iterator& begin, const Iterator& end ) :
    SectionBase( head, begin, end ) {};
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

      TestBase section( asHead(head), begin, end );

      AND_THEN( "we can get the parameters from it" ) {
        verifySection( section );
      } // AND_THEN
    } // THEN
  } // GIVEN

  WHEN( "the section is created from parameters" ) {

    THEN( "the section can be constructed" ) {

      std::vector< DataRecord > lists;
      std::vector<double> data1 = {7.705020e-4, 1.023642e+3};
      lists.emplace_back( 293.6, 2, 1, 2, std::move( data1 ) );
      std::vector<double> data2 = {9.306457e-3, 2.031301e+2};
      lists.emplace_back( 293.6, 2, 1, 3, std::move( data2 ) );

      TestBase section( 92235., 0.0, 1, 1, 1, 0, 3, lists );

      AND_THEN( "we can get the parameters from it" ) {
        verifySection( section );
      } // AND_THEN
    } // THEN
  } // WHEN

} // SCENARIO

std::string chunk(){

  return
    " 9.223500+4 0.000000+0          1          1          0          39228 3  1    1\n"
    " 2.936000+2 0.000000+0          2          1          2          29228 3  1    2\n"
    " 7.705020-4 1.023642+3                                            9228 3  1    3\n"
    " 2.936000+2 0.000000+0          2          1          2          39228 3  1    4\n"
    " 9.306457-3 2.031301+2                                            9228 3  1    5\n"
    "                                                                  9228 3  099999\n";
}

void verifySection( TestBase section ) {
  
  // header information
  REQUIRE( 1 == section.MT() );
  REQUIRE( 1 == section.sectionNumber() );
  REQUIRE( 92235 == section.ZA() );
  REQUIRE( 0.0 == section.atomicWeightRatio() );
  REQUIRE( 0.0 == section.AWR() );
  REQUIRE( 1 == section.NL() );
  REQUIRE( 1 == section.numLegendre() );
  REQUIRE( 0 == section.legendreOrder() );
  REQUIRE( 1 == section.NZ() );
  REQUIRE( 1 == section.numDilutions() );
  REQUIRE( 0 == section.LRFLAG() );
  REQUIRE( 0 == section.complexBreakUp() );
  REQUIRE( 3 == section.NGN() );
  REQUIRE( 3 == section.numGroups() );

  // access lists
  REQUIRE( 2 == section.records().size() );
  REQUIRE( 9.306457e-3 == Approx( section.record(3).list()[0] ) );
  REQUIRE( section.hasRecord(2) );
  REQUIRE( !section.hasRecord(1) );
  REQUIRE( !section.hasRecord(4) );
}
