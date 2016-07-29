#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "utility.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "TapeSkeleton Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "TapeSkeleton Complete!";
  return result;
}

using namespace ENDFtk::implementation;

SCENARIO( "Creating a tape Skeleton of an ENDF File" ){
  GIVEN( "a string representation of a Tape" ){
    std::string filename("n-001_H_001.endf");
    std::string sTape = utility::slurpFileToMemory( filename );

    std::string sTPID(sTape.begin(), sTape.begin()+76);
    std::string sTEND(sTape.end()-76, sTape.end());

    // Duplicate material for testing purposes
    sTape.erase(0,76); // Get rid of TPID
    sTape.erase(sTape.end()-76, sTape.end()); // Get rid of TEND

    sTape = sTPID + sTape + sTape;

    auto begin = sTape.begin();
    long LN = 1;

    WHEN( "a valid TEND record ends the Tape" ){
      sTape += sTEND;

      auto end = sTape.end();
      TapeSkeleton<std::string::iterator> tSkel(begin, end, LN);

      THEN( "we can access the parts of the skeleton" ){
        REQUIRE( 4419 == LN );
        REQUIRE( sTape.begin() == tSkel.begin() );
        REQUIRE( end == tSkel.end() );
        REQUIRE( 2 == tSkel.size() );

        AND_THEN( "we can access the Materials of the skeleton" ){
          tSkel[125];
        }
        AND_THEN( "an excpetion is thrown for an invalid index" ){
          REQUIRE_THROWS( tSkel[1] );
        }
      }
    }
    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){

      std::string sTEND = 
        "                                                                     0 0  0\n";
      sTape += sTEND;

      auto end = sTape.end();
      LOG(INFO) << "Expecting errors  when there is no TEND.";
      REQUIRE_THROWS(
        TapeSkeleton<std::string::iterator> tSkel(begin, end, LN) );

    }
    WHEN( "the Tape isn't long enough" ){
      auto end = sTape.end(); // There is already no TEND
      LOG(INFO) << "Expecting errors  when the tape isn't long enough.";
      REQUIRE_THROWS(
        TapeSkeleton<std::string::iterator> tSkel(begin, end, LN) );
    }

  } // GIVEN
} // SCENARIO
