#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string validSEND();
std::string invalidSEND();

class TestBaseWithoutMT : public section::BaseWithoutMT < TestBaseWithoutMT > {

public:

  TestBaseWithoutMT( double ZA, double AWR ) : BaseWithoutMT( ZA, AWR ) {};
  TestBaseWithoutMT( const HEAD& head, int MAT, int MF ) :
    BaseWithoutMT( head, MAT, MF ) {};

  int sectionNumber() const { return 451; }
};

SCENARIO( "section::BaseWithoutMT tests") {

  GIVEN( "a string representing the Section" ) {

    std::string line = chunk();
    auto begin = line.begin();
    auto end = line.end();
    long lineNumber = 2;
    auto head = StructureDivision( begin, end, lineNumber );

    std::unique_ptr<TestBaseWithoutMT> base;
    WHEN( "given good MAT, MF numbers" ){

      int MAT = 125;
      int MF = 3;
      THEN( "the base can be constructed without throwing" ) {

        REQUIRE_NOTHROW(
            base = std::make_unique<TestBaseWithoutMT>( asHead(head), MAT, MF) );

        AND_THEN( "we can get the ZA, MT, and atomicWeightRatio" ) {

          REQUIRE( 451 == base->MT() );
          REQUIRE( 451 == base->sectionNumber() );
          REQUIRE( 1001 == base->ZA() );
          REQUIRE( 0.9991673 == base->atomicWeightRatio() );
        } // AND_THEN
      } // THEN
    } // WHEN

    WHEN( "given bad MAT and MF numbers" ) {

      int MAT = 1;
      int MF = 1;

      THEN( "an exception is thrown on construction" ) {

        REQUIRE_THROWS( TestBaseWithoutMT( asHead( head ), MAT, MF ) );
        REQUIRE_THROWS( TestBaseWithoutMT( asHead( head ), MAT, 3 ) );
        REQUIRE_THROWS( TestBaseWithoutMT( asHead( head ), 125, MF ) );
      }
    }

    WHEN( "head parameters are negative" ) {

      REQUIRE_THROWS( TestBaseWithoutMT( -1, 2.0 ) );
      REQUIRE_THROWS( TestBaseWithoutMT( 1, -2.0 ) );
    }

    WHEN( "reading the SEND record" ) {

      base = std::make_unique< TestBaseWithoutMT >( asHead(head), 125, 3);
      std::string sSEND = validSEND();
      auto beginSEND = sSEND.begin();
      auto endSEND = sSEND.end();

      THEN( "reading SEND with valid MAT, and MF does not throw" ) {
          
        REQUIRE_NOTHROW( base->readSEND( beginSEND, endSEND,
                                         lineNumber, 125, 3 ) );
      }

      THEN( "reading SEND with invalid MAT, and MF throws an exception" ) {

        beginSEND = sSEND.begin();
        endSEND = sSEND.end();
        REQUIRE_THROWS( base->readSEND( beginSEND, endSEND,
                                        lineNumber, 125, 125 ) );

        beginSEND = sSEND.begin();
        endSEND = sSEND.end();
        REQUIRE_THROWS( base->readSEND( beginSEND, endSEND,
                                        lineNumber, 3, 3 ) );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk(){

  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n";
}

std::string validSEND() {
  return
    "                                                                   125 3  0     \n";
}
std::string invalidSEND() {
  return
    "                                                                   125 3  1     \n";
}
