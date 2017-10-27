#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1456 = section::Type< 1, 456 >;

std::string baseLNU1();
std::string baseLNU2();
std::string invalidLNU();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 456 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 456 with LNU=1" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLNU1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 456 > can be constructed and members can be tested" ) {
        section::Type< 1, 456 > MF1MT456( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::experimental::get< nubar::Polynomial >
                         ( MF1MT456.nubar() ) );

        const auto& data = std::experimental::get< nubar::Polynomial >
                           ( MF1MT456.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 456 == MF1MT456.MT() );
        REQUIRE( 456 == MF1MT456.sectionNumber() );
        REQUIRE( 92235 == MF1MT456.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT456.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT456.AWR() ) );
        REQUIRE( 1 == MF1MT456.LNU() );
        REQUIRE( 1 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );

        REQUIRE( 3 == MF1MT456.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLNU1() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 456 > can be constructed and members can be tested" ){
        section::Type< 1, 456 > MF1MT456 = section.parse< 1, 456 >( lineNumber );

        REQUIRE_NOTHROW( std::experimental::get< nubar::Polynomial >
                         ( MF1MT456.nubar() ) );

        const auto& data = std::experimental::get< nubar::Polynomial >
                           ( MF1MT456.nubar() );
        auto coefficients = data.coefficients();

        REQUIRE( 456 == MF1MT456.MT() );
        REQUIRE( 456 == MF1MT456.sectionNumber() );
        REQUIRE( 92235 == MF1MT456.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT456.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT456.AWR() ) );
        REQUIRE( 1 == MF1MT456.LNU() );
        REQUIRE( 1 == data.NCO() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );

        REQUIRE( 3 == MF1MT456.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLNU1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1456( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 456 with LNU=2" ) {

    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLNU2() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 456 > can be constructed and members can be tested" ) {
        section::Type< 1, 456 > MF1MT456( head, begin, end, lineNumber, 9228 );

        REQUIRE_NOTHROW( std::experimental::get< nubar::Tabulated >
                         ( MF1MT456.nubar() ) );

        const auto& data = std::experimental::get< nubar::Tabulated >
                           ( MF1MT456.nubar() );
        auto energy = data.energy();
        auto nubar = data.nubar();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 456 == MF1MT456.MT() );
        REQUIRE( 456 == MF1MT456.sectionNumber() );
        REQUIRE( 92235 == MF1MT456.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT456.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT456.AWR() ) );
        REQUIRE( 2 == MF1MT456.LNU() );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 5 == MF1MT456.NC() );
      }
    }

    WHEN( "there is a syntaxTree::Section" ){
      std::string sectionString = baseLNU2() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        section( head, begin, position, end, lineNumber );
      
      THEN( "a section::Type< 1, 456 > can be constructed and members can be tested" ){
        section::Type< 1, 456 > MF1MT456 = section.parse< 1, 456 >( lineNumber );

        REQUIRE_NOTHROW( std::experimental::get< nubar::Tabulated >
                         ( MF1MT456.nubar() ) );

        const auto& data = std::experimental::get< nubar::Tabulated >
                           ( MF1MT456.nubar() );
        auto energy = data.energy();
        auto nubar = data.nubar();
        auto interpolants = data.interpolants();
        auto boundaries = data.boundaries();

        REQUIRE( 456 == MF1MT456.MT() );
        REQUIRE( 456 == MF1MT456.sectionNumber() );
        REQUIRE( 92235 == MF1MT456.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT456.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT456.AWR() ) );
        REQUIRE( 2 == MF1MT456.LNU() );
        REQUIRE( 1 == data.NR() );
        REQUIRE( 1 == interpolants.size() );
        REQUIRE( 1 == boundaries.size() );
        REQUIRE( 4 == data.NP() );
        REQUIRE( 4 == energy.size() );
        REQUIRE( 4 == nubar.size() );
        REQUIRE( 1e-5 == Approx( energy[0] ) );
        REQUIRE( 0.0253 == Approx( energy[1] ) );
        REQUIRE( 0.05 == Approx( energy[2] ) );
        REQUIRE( 2e+7 == Approx( energy[3] ) );
        REQUIRE( 2.4367 == Approx( nubar[0] ) );
        REQUIRE( 2.4367 == Approx( nubar[1] ) );
        REQUIRE( 2.4367 == Approx( nubar[2] ) );
        REQUIRE( 5.209845 == Approx( nubar[3] ) );
        REQUIRE( 2 == interpolants[0] );
        REQUIRE( 4 == boundaries[0] );

        REQUIRE( 5 == MF1MT456.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLNU2() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1456( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 456 > with LNU=1" ) {
    std::string string = baseLNU1() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 456 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of section::Type< 1, 456 > with LNU=2" ) {
    std::string string = baseLNU2() + validSEND();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    HeadRecord head( begin, end, lineNumber );
    section::Type< 1, 456 > section( head, begin, end, lineNumber, 9228 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 9228, 1 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 456"
         " with an invalid LNU" ){
    std::string sectionString = invalidLNU() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1456( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseLNU1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          1          09228 1456     \n"
    " 2.436700+0                                                       9228 1456     \n";
}

std::string baseLNU2() {
  return
    " 9.223500+4 2.330248+2          0          2          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1456     \n"
    "          4          2                                            9228 1456     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1456     \n"
    " 2.000000+7 5.209845+0                                            9228 1456     \n";
}

std::string invalidLNU() {
  return
    " 9.223500+4 2.330248+2          0          3          0          09228 1456     \n"
    " 0.000000+0 0.000000+0          0          0          1          09228 1456     \n"
    " 2.436700+0                                                       9228 1456     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}

