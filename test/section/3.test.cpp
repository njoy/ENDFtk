// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/3.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
std::string chunkWithOneZone();
void verifyChunk( const section::Type< 3 >& );
void verifyChunkWithOneZone( const section::Type< 3 >& );
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

      THEN( "a section::Type< 3 > can be constructed and members can be tested" ) {

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

      THEN( "a section::Type< 3 > can be constructed and members can be tested" ) {

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

      tree::Section section( 125, 3, 102, std::string( sectionString ) );

      section::Type< 3 > chunk = section.parse< 3 >();

      THEN( "a section::Type< 3 > can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 3 > with a single interpolation region" ) {

    std::string sectionString = chunkWithOneZone() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 102;
      int zaid = 1001;
      double awr = 0.9991673;
      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      std::vector< double > energies = { 1e-5, 2e-5, 7.5e+5,
                                         1.9e+7, 1.95e+7, 2e+7 };
      std::vector< double > xs = { 1.672869e+1, 1.182897e+1, 3.347392e-5,
                                   2.751761e-5, 2.731301e-5, 2.710792e-5 };

      section::Type< 3 > chunk( mt, zaid, awr, qm, qi,
                                std::move( energies ), std::move( xs ) );

      THEN( "a section::Type< 3 > can be constructed and  members can be tested" ) {

        verifyChunkWithOneZone( chunk );
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

        verifyChunkWithOneZone( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 125, 3, 102, std::string( sectionString ) );

      section::Type< 3 > chunk = section.parse< 3 >();

      THEN( "a section::Type< 3 > can be constructed and members can be tested" ) {

        verifyChunkWithOneZone( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 125, 3 );

        CHECK( buffer == sectionString );
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
  CHECK( 102 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.LR() );
  CHECK( 0 == chunk.complexBreakUp() );
  CHECK_THAT( 2.224648e+6, WithinRel( chunk.QM() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( chunk.massDifferenceQValue() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.QI() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.reactionQValue() ) );

  CHECK( 6 == chunk.NP() );
  CHECK( 6 == chunk.numberPoints() );
  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberInterpolationRegions() );
  CHECK( 2 == chunk.INT().size() );
  CHECK( 2 == chunk.NBT().size() );
  CHECK( 5 == chunk.INT()[0] );
  CHECK( 2 == chunk.INT()[1] );
  CHECK( 3 == chunk.NBT()[0] );
  CHECK( 6 == chunk.NBT()[1] );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 5 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.interpolants()[1] );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( 6 == chunk.boundaries()[1] );
  CHECK( 6 == chunk.energies().size() );
  CHECK( 6 == chunk.crossSections().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2e-5, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.5e+5, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.9e+7, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 1.95e+7, WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[5] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 1.182897e+1, WithinRel( chunk.crossSections()[1] ) );
  CHECK_THAT( 3.347392e-5, WithinRel( chunk.crossSections()[2] ) );
  CHECK_THAT( 2.751761e-5, WithinRel( chunk.crossSections()[3] ) );
  CHECK_THAT( 2.731301e-5, WithinRel( chunk.crossSections()[4] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( chunk.crossSections()[5] ) );

  CHECK( 5 == chunk.NC() );
}

std::string chunkWithOneZone(){
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224648+6 3.224648+6          0          0          1          6 125 3102     \n"
    "          6          2                                             125 3102     \n"
    " 1.000000-5 1.672869+1 2.000000-5 1.182897+1 7.500000+5 3.347392-5 125 3102     \n"
    " 1.900000+7 2.751761-5 1.950000+7 2.731301-5 2.000000+7 2.710792-5 125 3102     \n";
}

void verifyChunkWithOneZone( const section::Type< 3 >& chunk ) {

  CHECK( 102 == chunk.MT() );
  CHECK( 102 == chunk.sectionNumber() );
  CHECK( 1001 == chunk.ZA() );
  CHECK( 1001 == chunk.targetIdentifier() );
  CHECK_THAT( 0.9991673, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 0.9991673, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.LR() );
  CHECK( 0 == chunk.complexBreakUp() );
  CHECK_THAT( 2.224648e+6, WithinRel( chunk.QM() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( chunk.massDifferenceQValue() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.QI() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.reactionQValue() ) );

  CHECK( 6 == chunk.NP() );
  CHECK( 6 == chunk.numberPoints() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 2 == chunk.INT()[0] );
  CHECK( 6 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants()[0] );
  CHECK( 6 == chunk.boundaries()[0] );
  CHECK( 6 == chunk.energies().size() );
  CHECK( 6 == chunk.crossSections().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2e-5, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.5e+5, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.9e+7, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 1.95e+7, WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.energies()[5] ) );
  CHECK_THAT( 1.672869e+1, WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 1.182897e+1, WithinRel( chunk.crossSections()[1] ) );
  CHECK_THAT( 3.347392e-5, WithinRel( chunk.crossSections()[2] ) );
  CHECK_THAT( 2.751761e-5, WithinRel( chunk.crossSections()[3] ) );
  CHECK_THAT( 2.731301e-5, WithinRel( chunk.crossSections()[4] ) );
  CHECK_THAT( 2.710792e-5, WithinRel( chunk.crossSections()[5] ) );

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
