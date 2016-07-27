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

    auto begin = sTape.begin();
    long LN = 1;

    WHEN( "a valid TEND record ends the Tape" ){

      auto end = sTape.end();
      TapeSkeleton<std::string::iterator> mSkel(begin, end, LN);

      REQUIRE( 2211 == LN );
      REQUIRE( sTape.begin() == mSkel.begin() );
      REQUIRE( end == mSkel.end() );
      REQUIRE( 1 == mSkel.size() );

    }
    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){
      sTape.erase(sTape.end()-76, sTape.end()); // Get rid of TEND

      std::string sTEND = 
        "                                                                     0 0  0\n";
      sTape += sTEND;

      auto end = sTape.end();
      LOG(INFO) << "Expecting errors  when there is no TEND.";
      REQUIRE_THROWS(
        TapeSkeleton<std::string::iterator> mSkel(begin, end, LN) );

    }
    WHEN( "the Tape isn't long enough" ){
      auto end = sTape.end()-10525;
      LOG(INFO) << "Expecting errors  when the tape isn't long enough.";
      REQUIRE_THROWS(
        TapeSkeleton<std::string::iterator> mSkel(begin, end, LN) );
    }

  } // GIVEN
} // SCENARIO

