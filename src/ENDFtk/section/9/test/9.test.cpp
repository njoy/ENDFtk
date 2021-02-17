#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/9.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using Multiplicity = section::Type< 9 >::Multiplicity;

std::string chunk();
void verifyChunk( const section::Type< 9 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 9 >" ) {

  GIVEN( "valid data for a section::Type< 9 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 102;
      int zaid = 95241;
      int lis = 0;
      double awr = 2.389860e+2;

      std::vector< Multiplicity > multiplicities = {

        Multiplicity( 5.537755e+6, 5.537755e+6, 95242, 0,
                      { 2 }, { 3 }, { 1e-5, 3e+7 }, { 0.9, 0.52 } ),
        Multiplicity( 5.537755e+6, 5.489125e+6, 95242, 2,
                      { 2 }, { 3 }, { 1e-5, 3e+7 }, { 0.1, 0.48 } ), };

      section::Type< 9 > chunk( mt, zaid, awr, lis,
                                std::move( multiplicities ) );

      THEN( "a section::Type< 9 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 9 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 9 > chunk( head, begin, end, lineNumber, 9543 );

      THEN( "a section::Type< 9 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 9 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      tree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );

      section::Type< 9 > chunk = section.parse< 9 >();
      section::Type< 9 > chunk2 = section.parse< 9 >( lineNumber );
      section::Type< 9 > chunk3 = section.parse( 9_c );
      section::Type< 9 > chunk4 = section.parse( 9_c, lineNumber );

      THEN( "a section::Type< 9 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
        verifyChunk( chunk2 );
        verifyChunk( chunk3 );
        verifyChunk( chunk4 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        std::string buffer2;
        std::string buffer3;
        std::string buffer4;
        auto output = std::back_inserter( buffer );
        auto output2 = std::back_inserter( buffer2 );
        auto output3 = std::back_inserter( buffer3 );
        auto output4 = std::back_inserter( buffer4 );
        chunk.print( output, 9543, 9 );
        chunk2.print( output2, 9543, 9 );
        chunk3.print( output3, 9543, 9 );
        chunk4.print( output4, 9543, 9 );

        CHECK( buffer == sectionString );
        CHECK( buffer2 == sectionString );
        CHECK( buffer3 == sectionString );
        CHECK( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 9 >" ) {

    WHEN( "a string representation of a section::Type< 9 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 9 >( head, begin, end,
                                          lineNumber, 9543 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk() {

  return
    " 9.524100+4 2.389860+2          0          0          2          09543 9102     \n"
    " 5.537755+6 5.537755+6      95242          0          1          29543 9102     \n"
    "          2          3                                            9543 9102     \n"
    " 1.000000-5 9.000000-1 3.000000+7 5.200000-1                      9543 9102     \n"
    " 5.537755+6 5.489125+6      95242          2          1          29543 9102     \n"
    "          2          3                                            9543 9102     \n"
    " 1.000000-5 1.000000-1 3.000000+7 4.800000-1                      9543 9102     \n";
}

void verifyChunk( const section::Type< 9 >& chunk ) {

  CHECK( 102 == chunk.MT() );
  CHECK( 95241 == chunk.ZA() );
  CHECK( 2.389860e+2 == Approx( chunk.AWR() ) );
  CHECK( 2.389860e+2 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.LIS() );
  CHECK( 0 == chunk.excitedLevel() );

  CHECK( 2 == chunk.multiplicities().size() );

  auto multiplicity = chunk.multiplicities()[0];
  CHECK( 5.537755e+6 == Approx( multiplicity.QM() ) );
  CHECK( 5.537755e+6 == Approx( multiplicity.massDifferenceQValue() ) );
  CHECK( 5.537755e+6 == Approx( multiplicity.QI() ) );
  CHECK( 5.537755e+6 == Approx( multiplicity.reactionQValue() ) );
  CHECK( 95242 == multiplicity.IZAP() );
  CHECK( 95242 == multiplicity.productIdentifier() );
  CHECK( 0 == multiplicity.LFS() );
  CHECK( 0 == multiplicity.excitedLevel() );
  CHECK( 2 == multiplicity.NP() );
  CHECK( 1 == multiplicity.NR() );
  CHECK( 1 == multiplicity.interpolants().size() );
  CHECK( 1 == multiplicity.boundaries().size() );
  CHECK( 3 == multiplicity.interpolants()[0] );
  CHECK( 2 == multiplicity.boundaries()[0] );
  CHECK( 2 == multiplicity.energies().size() );
  CHECK( 2 == multiplicity.multiplicities().size() );
  CHECK( 1e-5 == Approx( multiplicity.energies()[0] ) );
  CHECK( 3e+7 == Approx( multiplicity.energies()[1] ) );
  CHECK( 0.9 == Approx( multiplicity.multiplicities()[0] ) );
  CHECK( 0.52 == Approx( multiplicity.multiplicities()[1] ) );

  multiplicity = chunk.multiplicities()[1];
  CHECK( 5.537755e+6 == Approx( multiplicity.QM() ) );
  CHECK( 5.537755e+6 == Approx( multiplicity.massDifferenceQValue() ) );
  CHECK( 5.489125e+6 == Approx( multiplicity.QI() ) );
  CHECK( 5.489125e+6 == Approx( multiplicity.reactionQValue() ) );
  CHECK( 95242 == multiplicity.IZAP() );
  CHECK( 95242 == multiplicity.productIdentifier() );
  CHECK( 2 == multiplicity.LFS() );
  CHECK( 2 == multiplicity.excitedLevel() );
  CHECK( 2 == multiplicity.NP() );
  CHECK( 1 == multiplicity.NR() );
  CHECK( 1 == multiplicity.interpolants().size() );
  CHECK( 1 == multiplicity.boundaries().size() );
  CHECK( 3 == multiplicity.interpolants()[0] );
  CHECK( 2 == multiplicity.boundaries()[0] );
  CHECK( 2 == multiplicity.energies().size() );
  CHECK( 2 == multiplicity.multiplicities().size() );
  CHECK( 1e-5 == Approx( multiplicity.energies()[0] ) );
  CHECK( 3e+7 == Approx( multiplicity.energies()[1] ) );
  CHECK( 0.1 == Approx( multiplicity.multiplicities()[0] ) );
  CHECK( 0.48 == Approx( multiplicity.multiplicities()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                  9543 9  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                  9543 9  1     \n";
}