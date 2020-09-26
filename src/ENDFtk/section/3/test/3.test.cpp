#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/3.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 3 >" ) {

  GIVEN( "valid data for a section::Type< 3 >" ) {

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

    THEN( "a section::Type< 3 > can be constructed and "
          "members can be tested" ) {

      section::Type< 3 > chunk( mt, zaid, awr, qm, qi, lr,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ), std::move( xs ) );

      REQUIRE( 102 == chunk.MT() );
      REQUIRE( 1001 == chunk.ZA() );
      REQUIRE( 0.9991673 == Approx( chunk.AWR() ) );
      REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
      REQUIRE( 0 == chunk.LR() );
      REQUIRE( 0 == chunk.complexBreakUp() );
      REQUIRE( 2.224648e+6 == Approx( chunk.QM() ) );
      REQUIRE( 2.224648e+6 == Approx( chunk.massDifferenceQValue() ) );
      REQUIRE( 3.224648e+6 == Approx( chunk.QI() ) );
      REQUIRE( 3.224648e+6 == Approx( chunk.reactionQValue() ) );

      REQUIRE( 6 == chunk.NP() );
      REQUIRE( 2 == chunk.NR() );
      REQUIRE( 2 == chunk.interpolants().size() );
      REQUIRE( 2 == chunk.boundaries().size() );
      REQUIRE( 5 == chunk.interpolants()[0] );
      REQUIRE( 2 == chunk.interpolants()[1] );
      REQUIRE( 3 == chunk.boundaries()[0] );
      REQUIRE( 6 == chunk.boundaries()[1] );
      REQUIRE( 6 == chunk.energies().size() );
      REQUIRE( 6 == chunk.crossSections().size() );
      REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
      REQUIRE( 2e-5 == Approx( chunk.energies()[1] ) );
      REQUIRE( 7.5e+5 == Approx( chunk.energies()[2] ) );
      REQUIRE( 1.9e+7 == Approx( chunk.energies()[3] ) );
      REQUIRE( 1.95e+7 == Approx( chunk.energies()[4] ) );
      REQUIRE( 2e+7 == Approx( chunk.energies()[5] ) );
      REQUIRE( 1.672869e+1 == Approx( chunk.crossSections()[0] ) );
      REQUIRE( 1.182897e+1 == Approx( chunk.crossSections()[1] ) );
      REQUIRE( 3.347392e-5 == Approx( chunk.crossSections()[2] ) );
      REQUIRE( 2.751761e-5 == Approx( chunk.crossSections()[3] ) );
      REQUIRE( 2.731301e-5 == Approx( chunk.crossSections()[4] ) );
      REQUIRE( 2.710792e-5 == Approx( chunk.crossSections()[5] ) );

      REQUIRE( 5 == chunk.NC() );
    } // THEN
  } // GIVEN

  GIVEN( "a valid string representation of a section::Type< 3 >" ) {

    WHEN( "there is a valid SEND record" ) {
      std::string sectionString = chunk() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type< 3 > can be constructed and "
            "members can be tested" ) {

        section::Type< 3 > chunk( head, begin, end, lineNumber, 125 );

        REQUIRE( 102 == chunk.MT() );
        REQUIRE( 1001 == chunk.ZA() );
        REQUIRE( 0.9991673 == Approx( chunk.AWR() ) );
        REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
        REQUIRE( 0 == chunk.LR() );
        REQUIRE( 0 == chunk.complexBreakUp() );
        REQUIRE( 2.224648e+6 == Approx( chunk.QM() ) );
        REQUIRE( 2.224648e+6 == Approx( chunk.massDifferenceQValue() ) );
        REQUIRE( 3.224648e+6 == Approx( chunk.QI() ) );
        REQUIRE( 3.224648e+6 == Approx( chunk.reactionQValue() ) );

        REQUIRE( 6 == chunk.NP() );
        REQUIRE( 2 == chunk.NR() );
        REQUIRE( 2 == chunk.interpolants().size() );
        REQUIRE( 2 == chunk.boundaries().size() );
        REQUIRE( 5 == chunk.interpolants()[0] );
        REQUIRE( 2 == chunk.interpolants()[1] );
        REQUIRE( 3 == chunk.boundaries()[0] );
        REQUIRE( 6 == chunk.boundaries()[1] );
        REQUIRE( 6 == chunk.energies().size() );
        REQUIRE( 6 == chunk.crossSections().size() );
        REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
        REQUIRE( 2e-5 == Approx( chunk.energies()[1] ) );
        REQUIRE( 7.5e+5 == Approx( chunk.energies()[2] ) );
        REQUIRE( 1.9e+7 == Approx( chunk.energies()[3] ) );
        REQUIRE( 1.95e+7 == Approx( chunk.energies()[4] ) );
        REQUIRE( 2e+7 == Approx( chunk.energies()[5] ) );
        REQUIRE( 1.672869e+1 == Approx( chunk.crossSections()[0] ) );
        REQUIRE( 1.182897e+1 == Approx( chunk.crossSections()[1] ) );
        REQUIRE( 3.347392e-5 == Approx( chunk.crossSections()[2] ) );
        REQUIRE( 2.751761e-5 == Approx( chunk.crossSections()[3] ) );
        REQUIRE( 2.731301e-5 == Approx( chunk.crossSections()[4] ) );
        REQUIRE( 2.710792e-5 == Approx( chunk.crossSections()[5] ) );

        REQUIRE( 5 == chunk.NC() );
      } // THEN
    } // WHEN

//    WHEN( "there is a syntaxTree::Section" ){
//      std::string sectionString = chunk() + validSEND();
//      auto begin = sectionString.begin();
//      auto position = begin;
//      auto end = sectionString.end();
//      long lineNumber = 0;
//      auto head = HEAD( position, end, lineNumber );
//      syntaxTree::Section< std::string::iterator >
//        section( head, begin, position, end, lineNumber );
//
//      THEN( "a section::Type< 3 > can be constructed and "
//            "members can be tested" ) {
//
//        section::Type<3> chunk = section.parse< 3 >();
//        section::Type<3> chunk2 = section.parse< 3 >( lineNumber );
//        section::Type<3> chunk3 = section.parse( 3_c );
//        section::Type<3> chunk4 = section.parse( 3_c, lineNumber );
//
//        REQUIRE( 102 == chunk.MT() );
//        REQUIRE( 1001 == chunk.ZA() );
//        REQUIRE( 0.9991673 == Approx( chunk.AWR() ) );
//        REQUIRE( 0.9991673 == Approx( chunk.atomicWeightRatio() ) );
//        REQUIRE( 0 == chunk.LR() );
//        REQUIRE( 0 == chunk.complexBreakUp() );
//        REQUIRE( 2.224648e+6 == Approx( chunk.QM() ) );
//        REQUIRE( 2.224648e+6 == Approx( chunk.massDifferenceQValue() ) );
//        REQUIRE( 3.224648e+6 == Approx( chunk.QI() ) );
//        REQUIRE( 3.224648e+6 == Approx( chunk.reactionQValue() ) );
//
//        REQUIRE( 6 == chunk.NP() );
//        REQUIRE( 2 == chunk.NR() );
//        REQUIRE( 2 == chunk.interpolants().size() );
//        REQUIRE( 2 == chunk.boundaries().size() );
//        REQUIRE( 5 == chunk.interpolants()[0] );
//        REQUIRE( 2 == chunk.interpolants()[1] );
//        REQUIRE( 3 == chunk.boundaries()[0] );
//        REQUIRE( 6 == chunk.boundaries()[1] );
//        REQUIRE( 6 == chunk.energies().size() );
//        REQUIRE( 6 == chunk.crossSections().size() );
//        REQUIRE( 1e-5 == Approx( chunk.energies()[0] ) );
//        REQUIRE( 2e-5 == Approx( chunk.energies()[1] ) );
//        REQUIRE( 7.5e+5 == Approx( chunk.energies()[2] ) );
//        REQUIRE( 1.9e+7 == Approx( chunk.energies()[3] ) );
//        REQUIRE( 1.95e+7 == Approx( chunk.energies()[4] ) );
//        REQUIRE( 2e+7 == Approx( chunk.energies()[5] ) );
//        REQUIRE( 1.672869e+1 == Approx( chunk.crossSections()[0] ) );
//        REQUIRE( 1.182897e+1 == Approx( chunk.crossSections()[1] ) );
//        REQUIRE( 3.347392e-5 == Approx( chunk.crossSections()[2] ) );
//        REQUIRE( 2.751761e-5 == Approx( chunk.crossSections()[3] ) );
//        REQUIRE( 2.731301e-5 == Approx( chunk.crossSections()[4] ) );
//        REQUIRE( 2.710792e-5 == Approx( chunk.crossSections()[5] ) );
//
//        REQUIRE( 5 == chunk.NC() );
//
//        REQUIRE( 102 == chunk2.MT() );
//        REQUIRE( 1001 == chunk2.ZA() );
//        REQUIRE( 102 == chunk3.MT() );
//        REQUIRE( 1001 == chunk3.ZA() );
//        REQUIRE( 102 == chunk4.MT() );
//        REQUIRE( 1001 == chunk4.ZA() );
//
//      } // THEN
//    } // WHEN

    WHEN( "the SEND Record is not valid, i.e., MT!=0" ){
      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section::Type<3>( head, begin, end, lineNumber, 125 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 3 >" ) {
    std::string string = chunk() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    section::Type< 3 > chunk( head, begin, end, lineNumber, 125 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 125, 3 );
      REQUIRE( buffer == string );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk(){
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224648+6 3.224648+6          0          0          2          6 125 3102     \n"
    "          3          5          6          2                       125 3102     \n"
    " 1.000000-5 1.672869+1 2.000000-5 1.182897+1 7.500000+5 3.347392-5 125 3102     \n"
    " 1.900000+7 2.751761-5 1.950000+7 2.731301-5 2.000000+7 2.710792-5 125 3102     \n";
}

std::string validSEND(){
  return
    "                                                                   125 3  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                   125 3  1     \n";
}
