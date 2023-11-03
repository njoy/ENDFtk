#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/451.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ElementInformation = section::Type< 7, 451 >::ElementInformation;

// macros don't like multiple template arguments
using section7451 = section::Type< 7, 451 >;

std::string chunk();
void verifyChunk( const section::Type< 7, 451 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 7, 451 >" ) {

  GIVEN( "valid data for a section::Type< 7, 451 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly for a single element" ) {

      double za = 122.;
      double awr = 15.;

      ElementInformation element( 2,
                                  { 8016, 8017, 8018 }, { 0, 0, 0 },
                                  { .99762, 3.8e-4, 2e-3 },
                                  { 15.85751, 16.8531, 17.8445 },
                                  { 3.744801, 3.642671, 3.846775 } );


      section::Type< 7, 451 > chunk( za, awr, std::move( element ) );

      THEN( "a section::Type< 7, 451 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 22, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 451 > chunk( head, begin, end, lineNumber, 22 );

      THEN( "a section::Type< 7, 451 > can be constructed and members can be "
          "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 22, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 22, 7, 451, std::string( sectionString ) );

      section::Type< 7, 451 > chunk = section.parse< 7, 451 >();

      THEN( "a section::Type< 7, 451 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 22, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 7, 451 >" ) {

    WHEN( "a string representation of a section::Type< 7, 451 > with an "
          "invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section7451( head, begin, end, lineNumber, 22 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.220000+2 1.500000+1          1          0          0          0  22 7451     \n"
    " 0.000000+0 0.000000+0          2          0         18          3  22 7451     \n"
    " 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n"
    " 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n"
    " 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0 0.000000+0  22 7451     \n";
}

void verifyChunk( const section::Type< 7, 451 >& chunk ) {

  CHECK( 451 == chunk.MT() );
  CHECK( 451 == chunk.sectionNumber() );

  CHECK( 122. == Approx( chunk.ZA() ) );
  CHECK( 15. == Approx( chunk.AWR() ) );
  CHECK( 1 == chunk.NA() );
  CHECK( 1 == chunk.numberElements() );

  CHECK( 1 == chunk.elements().size() );

  CHECK( 2 == chunk.elements()[0].NAS() );
  CHECK( 2 == chunk.elements()[0].numberAtoms() );
  CHECK( 3 == chunk.elements()[0].NI() );
  CHECK( 3 == chunk.elements()[0].numberIsotopes() );

  CHECK( 3 == chunk.elements()[0].ZAI().size() );
  CHECK( 3 == chunk.elements()[0].isotopeIdentifiers().size() );
  CHECK( 3 == chunk.elements()[0].LISI().size() );
  CHECK( 3 == chunk.elements()[0].isomericStates().size() );
  CHECK( 3 == chunk.elements()[0].AFI().size() );
  CHECK( 3 == chunk.elements()[0].abundances().size() );
  CHECK( 3 == chunk.elements()[0].AWRI().size() );
  CHECK( 3 == chunk.elements()[0].atomicWeightRatios().size() );
  CHECK( 3 == chunk.elements()[0].SFI().size() );
  CHECK( 3 == chunk.elements()[0].freeScatteringCrossSections().size() );
  CHECK( 8016 == chunk.elements()[0].ZAI()[0] );
  CHECK( 8017 == chunk.elements()[0].ZAI()[1] );
  CHECK( 8018 == chunk.elements()[0].ZAI()[2] );
  CHECK( 8016 == chunk.elements()[0].isotopeIdentifiers()[0] );
  CHECK( 8017 == chunk.elements()[0].isotopeIdentifiers()[1] );
  CHECK( 8018 == chunk.elements()[0].isotopeIdentifiers()[2] );
  CHECK( 0 == chunk.elements()[0].LISI()[0] );
  CHECK( 0 == chunk.elements()[0].LISI()[1] );
  CHECK( 0 == chunk.elements()[0].LISI()[2] );
  CHECK( 0 == chunk.elements()[0].isomericStates()[0] );
  CHECK( 0 == chunk.elements()[0].isomericStates()[1] );
  CHECK( 0 == chunk.elements()[0].isomericStates()[2] );
  CHECK( 9.976200e-1 == Approx( chunk.elements()[0].AFI()[0] ) );
  CHECK( 3.800000e-4 == Approx( chunk.elements()[0].AFI()[1] ) );
  CHECK( 2.000000e-3 == Approx( chunk.elements()[0].AFI()[2] ) );
  CHECK( 9.976200e-1 == Approx( chunk.elements()[0].abundances()[0] ) );
  CHECK( 3.800000e-4 == Approx( chunk.elements()[0].abundances()[1] ) );
  CHECK( 2.000000e-3 == Approx( chunk.elements()[0].abundances()[2] ) );
  CHECK(    15.85751 == Approx( chunk.elements()[0].AWRI()[0] ) );
  CHECK(    16.85310 == Approx( chunk.elements()[0].AWRI()[1] ) );
  CHECK(    17.84450 == Approx( chunk.elements()[0].AWRI()[2] ) );
  CHECK(    15.85751 == Approx( chunk.elements()[0].atomicWeightRatios()[0] ) );
  CHECK(    16.85310 == Approx( chunk.elements()[0].atomicWeightRatios()[1] ) );
  CHECK(    17.84450 == Approx( chunk.elements()[0].atomicWeightRatios()[2] ) );
  CHECK(    3.744801 == Approx( chunk.elements()[0].SFI()[0] ) );
  CHECK(    3.642671 == Approx( chunk.elements()[0].SFI()[1] ) );
  CHECK(    3.846775 == Approx( chunk.elements()[0].SFI()[2] ) );
  CHECK(    3.744801 == Approx( chunk.elements()[0].freeScatteringCrossSections()[0] ) );
  CHECK(    3.642671 == Approx( chunk.elements()[0].freeScatteringCrossSections()[1] ) );
  CHECK(    3.846775 == Approx( chunk.elements()[0].freeScatteringCrossSections()[2] ) );

  CHECK( 5 == chunk.NC() );
}

std::string validSEND() {
  return
    "                                                                    22 7  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                    22 7  4     \n";
}
