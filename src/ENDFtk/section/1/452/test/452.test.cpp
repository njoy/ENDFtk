#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

using section1452 = section::Type< 1, 452 >;

std::string baseLNU1();
std::string baseLNU2();
std::string invalidLNU();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 1, 452 >" ) {
  GIVEN( "a string representation of a valid File 1 Section 452 with LNU=1" ) {
    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLNU1() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 452 > can be constructed and members can be tested" ) {
        section::Type< 1, 452 > MF1MT452( head, begin, end, lineNumber, 9228 );
        REQUIRE( 452 == MF1MT452.MT() );
        REQUIRE( 92235 == MF1MT452.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT452.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT452.AWR() ) );
        REQUIRE( 1 == MF1MT452.LNU() );
        auto coefficients = MF1MT452.coefficients();
        REQUIRE( 2 == coefficients.size() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

//        REQUIRE( 3 == MF1MT452.NC() );
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
      
      THEN( "a section::Type< 1, 452 > can be constructed and members can be tested" ){
        section::Type< 1, 452 > MF1MT452 = section.parse< 1, 452 >( lineNumber );
        REQUIRE( 452 == MF1MT452.MT() );
        REQUIRE( 92235 == MF1MT452.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT452.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT452.AWR() ) );
        REQUIRE( 1 == MF1MT452.LNU() );
        auto coefficients = MF1MT452.coefficients();
        REQUIRE( 2 == coefficients.size() );
        REQUIRE( 2.4367 == Approx( coefficients[0] ) );
        REQUIRE( 0.05 == Approx( coefficients[1] ) );

//        REQUIRE( 3 == MF1MT452.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLNU1() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1452( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of a valid File 1 Section 452 with LNU=2" ) {
    WHEN( "there is a valid SEND record" ){
      std::string sectionString = baseLNU2() + validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "a section::Type< 1, 452 > can be constructed and members can be tested" ) {
        section::Type< 1, 452 > MF1MT452( head, begin, end, lineNumber, 9228 );
        REQUIRE( 452 == MF1MT452.MT() );
        REQUIRE( 92235 == MF1MT452.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT452.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT452.AWR() ) );
        REQUIRE( 2 == MF1MT452.LNU() );

//        REQUIRE( 5 == MF1MT452.NC() );
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
      
      THEN( "a section::Type< 1, 452 > can be constructed and members can be tested" ){
        section::Type< 1, 452 > MF1MT452 = section.parse< 1, 452 >( lineNumber );
        REQUIRE( 452 == MF1MT452.MT() );
        REQUIRE( 92235 == MF1MT452.ZA() );
        REQUIRE( 233.0248 == Approx( MF1MT452.atomicWeightRatio() ) );
        REQUIRE( 233.0248 == Approx( MF1MT452.AWR() ) );
        REQUIRE( 2 == MF1MT452.LNU() );

//        REQUIRE( 5 == MF1MT452.NC() );
      }
    }
    
    WHEN( "the SEND Record is not valid, i.e., MT != 0" ){
      std::string sectionString = baseLNU2() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section1452( head, begin, end, lineNumber, 9228 ) );
      }
    } 
  } // GIVEN

  GIVEN( "a string representation of an File 1 Section 451"
         " with an invalid LNU" ){
    std::string sectionString = invalidLNU() + validSEND();
    auto begin = sectionString.begin();
    auto end = sectionString.end();
    long lineNumber = 1;
    HeadRecord head( begin, end, lineNumber );
    
    THEN( "an exception is thrown upon construction" ){
      REQUIRE_THROWS( section1452( head, begin, end, lineNumber, 9228 ) );
    }
  } // GIVEN
} // SCENARIO

std::string baseLNU1() {
  return
    " 9.223500+4 2.330248+2          0          1          0          09228 1452     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1452     \n"
    " 2.436700+0 5.000000-2                                            9228 1452     \n";
}

std::string baseLNU2() {
  return
    " 9.223500+4 2.330248+2          0          2          0          09228 1452     \n"
    " 0.000000+0 0.000000+0          0          0          1          49228 1452     \n"
    "          4          2                                            9228 1452     \n"
    " 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1452     \n"
    " 2.000000+7 5.209845+0                                            9228 1452     \n";
}

std::string invalidLNU() {
  return
    " 9.223500+4 2.330248+2          0          3          0          09228 1452     \n"
    " 0.000000+0 0.000000+0          0          0          2          09228 1452     \n"
    " 2.436700+0 5.000000-2                                            9228 1452     \n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                  9228 1  1     \n";
}

