#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/3.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const section::Type< 3 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 3 >" ) {

  GIVEN( "valid data for a section::Type< 3 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 102;
      int zaid = 1001;
      int lr = 0;
      double awr = 0.9991673;
      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      std::vector< long > interpolants = { 5, 2 };
      std::vector< long > boundaries = { 3, 6 };
      std::vector< double > energies = { 1e-5, 2e-5, 7.5e+5,
                                         1.9e+7, 1.95e+7, 2e+7 };
      std::vector< double > xs = { 1.672869e+1, 1.182897e+1, 3.347392e-5,
                                   2.751761e-5, 2.731301e-5, 2.710792e-5 };

      section::Type< 3 > chunk( mt, zaid, awr, qm, qi, lr,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ), std::move( xs ) );

      THEN( "a section::Type< 3 > can be constructed and "
            "members can be tested" ) {


        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 3 > chunk( head, begin, end, lineNumber, 125 );

      THEN( "a section::Type< 3 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3 );

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

      section::Type<3> chunk = section.parse< 3 >();
      section::Type<3> chunk2 = section.parse< 3 >( lineNumber );
      section::Type<3> chunk3 = section.parse( 3_c );
      section::Type<3> chunk4 = section.parse( 3_c, lineNumber );

      THEN( "a section::Type< 3 > can be constructed and "
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
        chunk.print( output, 125, 3 );
        chunk2.print( output2, 125, 3 );
        chunk3.print( output3, 125, 3 );
        chunk4.print( output4, 125, 3 );

        CHECK( buffer == sectionString );
        CHECK( buffer2 == sectionString );
        CHECK( buffer3 == sectionString );
        CHECK( buffer4 == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 3 >" ) {

    WHEN( "a string representation of a section::Type< 3 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 3 >( head, begin, end,
                                            lineNumber, 125 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk(){
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224648+6 3.224648+6          0          0          2          6 125 3102     \n"
    "          3          5          6          2                       125 3102     \n"
    " 1.000000-5 1.672869+1 2.000000-5 1.182897+1 7.500000+5 3.347392-5 125 3102     \n"
    " 1.900000+7 2.751761-5 1.950000+7 2.731301-5 2.000000+7 2.710792-5 125 3102     \n";
}

void verifyChunk( const section::Type< 3 >& chunk ) {

  CHECK( 102 == chunk.MT() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 0.9991673 == Approx( chunk.AWR() ) );
  CHECK( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.LR() );
  CHECK( 0 == chunk.complexBreakUp() );
  CHECK( 2.224648e+6 == Approx( chunk.QM() ) );
  CHECK( 2.224648e+6 == Approx( chunk.massDifferenceQValue() ) );
  CHECK( 3.224648e+6 == Approx( chunk.QI() ) );
  CHECK( 3.224648e+6 == Approx( chunk.reactionQValue() ) );

  CHECK( 6 == chunk.NP() );
  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 5 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.interpolants()[1] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 6 == chunk.boundaries()[1] );
  CHECK( 6 == chunk.energies().size() );
  CHECK( 6 == chunk.crossSections().size() );
  CHECK( 1e-5 == Approx( chunk.energies()[0] ) );
  CHECK( 2e-5 == Approx( chunk.energies()[1] ) );
  CHECK( 7.5e+5 == Approx( chunk.energies()[2] ) );
  CHECK( 1.9e+7 == Approx( chunk.energies()[3] ) );
  CHECK( 1.95e+7 == Approx( chunk.energies()[4] ) );
  CHECK( 2e+7 == Approx( chunk.energies()[5] ) );
  CHECK( 1.672869e+1 == Approx( chunk.crossSections()[0] ) );
  CHECK( 1.182897e+1 == Approx( chunk.crossSections()[1] ) );
  CHECK( 3.347392e-5 == Approx( chunk.crossSections()[2] ) );
  CHECK( 2.751761e-5 == Approx( chunk.crossSections()[3] ) );
  CHECK( 2.731301e-5 == Approx( chunk.crossSections()[4] ) );
  CHECK( 2.710792e-5 == Approx( chunk.crossSections()[5] ) );

  CHECK( 5 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                   125 3  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   125 3  1     \n";
}
