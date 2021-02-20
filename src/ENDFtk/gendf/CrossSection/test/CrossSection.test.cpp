#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/gendf/CrossSection.hpp"
#include <iostream>

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using namespace njoy::ENDFtk::gendf;

// forward declarations
std::string chunk();
void verifySection( const CrossSection& );

// helper function
template< typename Range1, typename Range2 >
void compareRanges( const Range1& r1, const Range2& r2 ) {

  CHECK( r1.size() == r2.size() );
  for( std::size_t i=0; i<r1.size(); ++i ) {
    CHECK( r1[i] == Approx(r2[i]) );
  }

}

// tests
SCENARIO( "CrossSection tests") {

  GIVEN( "valid data for the CrossSection" ) {

    WHEN( "the data is given as a string" ) {

      std::string line = chunk();
      auto begin = line.begin();
      auto end = line.end();
      long lineNumber = 0;
      auto head = StructureDivision( begin, end, lineNumber );

      THEN( "the section can be constructed" ) {

        CrossSection section( asHead(head), begin, end, lineNumber, 9228 );
        verifySection( section );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly" ) {

      std::vector< double > fluxes1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
      std::vector< double > xs1 = { 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
      std::vector< double > fluxes2 = { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 };
      std::vector< double > xs2 = { 7.1, 8.1, 9.1, 10.1, 11.1, 12.1 };

      THEN( "the section can be constructed" ) {


        // std::vector< DataRecord > records = {
        //   CrossSection::makeDataRecord( 293.6, 2, fluxes1, xs1 ),
        //   CrossSection::makeDataRecord( 293.6, 2, fluxes2, xs2 ) };
        // CrossSection section( 92235., 0.0, 1, 2, 3, 0, 3,
        //                       std::move( records ) );
        // verifySection( section );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk(){

  return
    " 9.223500+4 0.000000+0          2          3          0          39228 3  1     \n"
    " 2.936000+2 0.000000+0          2          1         12          19228 3  1     \n"
    "        0.0        0.0        0.0        0.0        0.0        0.09228 3  1     \n"
    "        0.0        0.0        0.0        0.0        0.0        0.09228 3  1     \n"
    " 2.936000+2 0.000000+0          2          1         12          29228 3  1     \n"
    "        1.0        2.0        3.0        4.0        5.0        6.09228 3  1     \n"
    "        7.0        8.0        9.0       10.0       11.0       12.09228 3  1     \n"
    " 2.936000+2 0.000000+0          2          1         12          39228 3  1     \n"
    "        1.1        2.1        3.1        4.1        5.1        6.19228 3  1     \n"
    "        7.1        8.1        9.1       10.1       11.1       12.19228 3  1     \n"
    "                                                                  9228 3  0     \n";
}

void verifySection( const CrossSection& section ) {

  // header information
  CHECK( 1 == section.MT() );
  CHECK( 1 == section.sectionNumber() );
  CHECK( 92235 == section.ZA() );
  CHECK( 0.0 == section.atomicWeightRatio() );
  CHECK( 0.0 == section.AWR() );
  CHECK( 2 == section.NL() );
  CHECK( 2 == section.numberLegendreMoments() );
  CHECK( 1 == section.legendreOrder() );
  CHECK( 3 == section.NZ() );
  CHECK( 3 == section.numberDilutions() );
  CHECK( 0 == section.LR() );
  CHECK( 0 == section.complexBreakUp() );
  CHECK( 3 == section.NGN() );
  CHECK( 3 == section.numberGroups() );

  // group not provided
  CHECK( 0.0 == Approx( section.flux(1) ) );
  CHECK( 0.0 == Approx( section.flux(1, 1, 1) ) );
  CHECK( 0.0 == Approx( section.crossSection(1) ) );
  CHECK( 0.0 == Approx( section.crossSection(1, 0, 0) ) );

  // group provided -- flux
  CHECK( 1.0 == Approx( section.flux(2) ) );
  CHECK( 1.0 == Approx( section.flux(2, 0, 0) ) );
  CHECK( 2.0 == Approx( section.flux(2, 1, 0) ) );
  CHECK( 3.0 == Approx( section.flux(2, 0, 1) ) );
  CHECK( 3.0 == Approx( section.flux(2, 1) ) );
  CHECK( 4.0 == Approx( section.flux(2, 1, 1) ) );
  CHECK( 5.0 == Approx( section.flux(2, 0, 2) ) );
  CHECK( 6.0 == Approx( section.flux(2, 1, 2) ) );

  // group provided -- cross_section
  CHECK( 7.1 == Approx( section.crossSection(3) ) );
  CHECK( 7.1 == Approx( section.crossSection(3, 0, 0) ) );
  CHECK( 8.1 == Approx( section.crossSection(3, 1, 0) ) );
  CHECK( 9.1 == Approx( section.crossSection(3, 0, 1) ) );
  CHECK( 10.1 == Approx( section.crossSection(3, 1, 1) ) );
  CHECK( 11.1 == Approx( section.crossSection(3, 0, 2) ) );
  CHECK( 11.1 == Approx( section.crossSection(3, 2) ) );
  CHECK( 12.1 == Approx( section.crossSection(3, 1, 2) ) );

  // vectors
  compareRanges( std::vector< double >( {0.0, 1.0, 1.1} ),
                 section.fluxes(0) );
  compareRanges( std::vector< double >( {0.0, 2.0, 2.1} ),
                 section.fluxes(1, 0) );
  compareRanges( std::vector< double >( {0.0, 7.0, 7.1} ),
                 section.crossSections(0) );
  compareRanges( std::vector< double >( {0.0, 10.0, 10.1} ),
                 section.crossSections(1, 1) );

}
