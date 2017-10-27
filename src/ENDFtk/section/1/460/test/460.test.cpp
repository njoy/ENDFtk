#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1460 = section::Type< 1, 460 >;

std::string baseLO1();
std::string baseLO2();
std::string invalidLO();
std::string invalidNG();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 460 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 460 with LO=1" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLO1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 460 > can be constructed and members can be tested" ) {
        section::Type< 1, 460 > MF1MT460( head, begin, end, lineNumber, 9228 );

        REQUIRE( 460 == MF1MT460.MT() );
        REQUIRE( 460 == MF1MT460.sectionNumber() );
        REQUIRE( 92235 == MF1MT460.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT460.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT460.AWR() ) );

        REQUIRE( 1 == MF1MT460.LO() );
        REQUIRE( 2 == MF1MT460.NG() );

        REQUIRE_NOTHROW( std::experimental::get< section1460::Discrete >
                         ( MF1MT460.delayedPhotons() ) );

        const auto& data = std::experimental::get< section1460::Discrete >
                           ( MF1MT460.delayedPhotons() );
        const auto& photons = data.photons();

        REQUIRE( 1 == data.LO() );
        REQUIRE( 2 == data.NG() );
        REQUIRE( 2 == photons.size() );

        section::Type< 1, 460 >::DiscretePhoton photon = photons[0];
        REQUIRE( 0.1 == Approx( photon.E() ) );
        REQUIRE( 1 == photon.index() );
        REQUIRE( 1 == photon.NR() );
        REQUIRE( 2 == photon.NP() );
        REQUIRE( 1 == photon.interpolants().size() );
        REQUIRE( 1 == photon.boundaries().size() );
        REQUIRE( 4 == photon.interpolants()[0] );
        REQUIRE( 2 == photon.boundaries()[0] );
        REQUIRE( 2 == photon.time().size() );
        REQUIRE( 2 == photon.multiplicity().size() );
        REQUIRE( 0. == Approx( photon.time()[0] ) );
        REQUIRE( 4. == Approx( photon.time()[1] ) );
        REQUIRE( 4.877451e-1 == Approx( photon.multiplicity()[0] ) );
        REQUIRE( 1.715686e-1 == Approx( photon.multiplicity()[1] ) );

        photon = photons[1];
        REQUIRE( 0.2 == Approx( photon.E() ) );
        REQUIRE( 2 == photon.index() );
        REQUIRE( 1 == photon.NR() );
        REQUIRE( 3 == photon.NP() );
        REQUIRE( 1 == photon.interpolants().size() );
        REQUIRE( 1 == photon.boundaries().size() );
        REQUIRE( 2 == photon.interpolants()[0] );
        REQUIRE( 3 == photon.boundaries()[0] );
        REQUIRE( 3 == photon.time().size() );
        REQUIRE( 3 == photon.multiplicity().size() );
        REQUIRE( 0. == Approx( photon.time()[0] ) );
        REQUIRE( 5. == Approx( photon.time()[1] ) );
        REQUIRE( 9. == Approx( photon.time()[2] ) );
        REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[0] ) );
        REQUIRE( 2.450980e-3 == Approx( photon.multiplicity()[1] ) );
        REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[2] ) );

        REQUIRE( 7 == MF1MT460.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLO1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 460 > can be constructed and members can be tested" ){
        section::Type< 1, 460 > MF1MT460 = section.parse< 1, 460 >( lineNumber );

        REQUIRE( 460 == MF1MT460.MT() );
        REQUIRE( 460 == MF1MT460.sectionNumber() );
        REQUIRE( 92235 == MF1MT460.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT460.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT460.AWR() ) );

        REQUIRE( 1 == MF1MT460.LO() );
        REQUIRE( 2 == MF1MT460.NG() );

        REQUIRE_NOTHROW( std::experimental::get< section1460::Discrete >
                         ( MF1MT460.delayedPhotons() ) );

        const auto& data = std::experimental::get< section1460::Discrete >
                           ( MF1MT460.delayedPhotons() );
        const auto& photons = data.photons();

        REQUIRE( 1 == data.LO() );
        REQUIRE( 2 == data.NG() );
        REQUIRE( 2 == photons.size() );

        section::Type< 1, 460 >::DiscretePhoton photon = photons[0];
        REQUIRE( 0.1 == Approx( photon.E() ) );
        REQUIRE( 1 == photon.index() );
        REQUIRE( 1 == photon.NR() );
        REQUIRE( 2 == photon.NP() );
        REQUIRE( 1 == photon.interpolants().size() );
        REQUIRE( 1 == photon.boundaries().size() );
        REQUIRE( 4 == photon.interpolants()[0] );
        REQUIRE( 2 == photon.boundaries()[0] );
        REQUIRE( 2 == photon.time().size() );
        REQUIRE( 2 == photon.multiplicity().size() );
        REQUIRE( 0. == Approx( photon.time()[0] ) );
        REQUIRE( 4. == Approx( photon.time()[1] ) );
        REQUIRE( 4.877451e-1 == Approx( photon.multiplicity()[0] ) );
        REQUIRE( 1.715686e-1 == Approx( photon.multiplicity()[1] ) );

        photon = photons[1];
        REQUIRE( 0.2 == Approx( photon.E() ) );
        REQUIRE( 2 == photon.index() );
        REQUIRE( 1 == photon.NR() );
        REQUIRE( 3 == photon.NP() );
        REQUIRE( 1 == photon.interpolants().size() );
        REQUIRE( 1 == photon.boundaries().size() );
        REQUIRE( 2 == photon.interpolants()[0] );
        REQUIRE( 3 == photon.boundaries()[0] );
        REQUIRE( 3 == photon.time().size() );
        REQUIRE( 3 == photon.multiplicity().size() );
        REQUIRE( 0. == Approx( photon.time()[0] ) );
        REQUIRE( 5. == Approx( photon.time()[1] ) );
        REQUIRE( 9. == Approx( photon.time()[2] ) );
        REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[0] ) );
        REQUIRE( 2.450980e-3 == Approx( photon.multiplicity()[1] ) );
        REQUIRE( 1.691176e-1 == Approx( photon.multiplicity()[2] ) );

        REQUIRE( 7 == MF1MT460.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLO1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 460 with LO=2" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLO2() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 460 > can be constructed and members can be tested" ) {
        section::Type< 1, 460 > MF1MT460( head, begin, end, lineNumber, 9228 );

        REQUIRE( 460 == MF1MT460.MT() );
        REQUIRE( 460 == MF1MT460.sectionNumber() );
        REQUIRE( 92235 == MF1MT460.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT460.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT460.AWR() ) );

        REQUIRE( 2 == MF1MT460.LO() );
        REQUIRE( 0 == MF1MT460.NG() );

        REQUIRE_NOTHROW( std::experimental::get< section1460::Continuous >
                         ( MF1MT460.delayedPhotons() ) );

        const auto& data = std::experimental::get< section1460::Continuous >
                           ( MF1MT460.delayedPhotons() );
        auto lambdas = data.lambdas();

        REQUIRE( 2 == data.LO() );
        REQUIRE( 0 == data.NG() );
        REQUIRE( 6 == data.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );

        REQUIRE( 3 == MF1MT460.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLO2() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 460 > can be constructed and members can be tested" ){
        section::Type< 1, 460 > MF1MT460 = section.parse< 1, 460 >( lineNumber );

        REQUIRE( 460 == MF1MT460.MT() );
        REQUIRE( 460 == MF1MT460.sectionNumber() );
        REQUIRE( 92235 == MF1MT460.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT460.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT460.AWR() ) );

        REQUIRE( 2 == MF1MT460.LO() );
        REQUIRE( 0 == MF1MT460.NG() );

        REQUIRE_NOTHROW( std::experimental::get< section1460::Continuous >
                         ( MF1MT460.delayedPhotons() ) );

        const auto& data = std::experimental::get< section1460::Continuous >
                           ( MF1MT460.delayedPhotons() );
        auto lambdas = data.lambdas();

        REQUIRE( 2 == data.LO() );
        REQUIRE( 0 == data.NG() );
        REQUIRE( 6 == data.NNF() );
        REQUIRE( 6 == lambdas.size() );
        REQUIRE( 0.013336 == Approx( lambdas[0] ) );
        REQUIRE( 0.032739 == Approx( lambdas[1] ) );
        REQUIRE( 0.12078 == Approx( lambdas[2] ) );
        REQUIRE( 0.30278 == Approx( lambdas[3] ) );
        REQUIRE( 0.84949 == Approx( lambdas[4] ) );
        REQUIRE( 2.853000 == Approx( lambdas[5] ) );

        REQUIRE( 3 == MF1MT460.NC() );
      }
    }

    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLO2() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 460 > with LO=1" ) {
    std::string string = baseLO1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 460 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 460 > with LO=2" ) {
    std::string string = baseLO2() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 460 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 460"
         " with an invalid LO" ){
    std::string sectionString = invalidLO() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 460"
         " with an invalid NG" ){
    std::string sectionString = invalidNG() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1460( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseLO1() {
  return
    " 9.223500+4 2.330248+2          1          0          2          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

std::string baseLO2() {
  return
    " 9.223500+4 2.330248+2          2          0          0          09228 1460     \n"
    " 0.000000+0 0.000000+0          0          0          6          09228 1460     \n"
    " 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n";
}

std::string invalidLO() {
  return
    " 9.223500+4 2.330248+2          0          0          2          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          39228 1460     \n"
    "          3          2                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

std::string invalidNG() {
  return
    " 9.223500+4 2.330248+2          1          0          0          09228 1460     \n"
    " 1.000000-1 0.000000+0          1          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n"
    " 2.000000-1 0.000000+0          2          0          1          29228 1460     \n"
    "          2          4                                            9228 1460     \n"
    " 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}

