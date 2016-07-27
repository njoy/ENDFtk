#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "utility.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "MaterialSkeleton Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "MaterialSkeleton Complete!";
  return result;
}

using namespace ENDFtk::implementation;

SCENARIO( "Creating a material Skeleton of an ENDF File" ){
  GIVEN( "a string representation of a Material" ){
    std::string filename("n-001_H_001.endf");
    std::string sMaterial = utility::slurpFileToMemory( filename );
    sMaterial.erase(0,76); // Get rid of TPID
    sMaterial.erase(sMaterial.end()-152, sMaterial.end()); // Get rid of MEND

    auto begin = sMaterial.begin();
    long LN = 1;

    WHEN( "a valid MEND record ends the Material" ){

      std::string sMEND = 
        "                                                                     0 0  0\n";
      sMaterial += sMEND;

      auto end = sMaterial.end();
      MaterialSkeleton<std::string::iterator> mSkel(begin, end, LN);

      REQUIRE( 2209 == LN );
      REQUIRE( sMaterial.begin() == mSkel.begin() );
      REQUIRE( end == mSkel.end() );
      REQUIRE( 6 == mSkel.size() );

      REQUIRE( 125 == mSkel.MAT() );
    }
    WHEN( "an invalid (MF!= 0) MEND record ends the Material" ){

      std::string sMEND = 
        "                                                                   125 0  0\n";
      sMaterial += sMEND;

      auto end = sMaterial.end();
      REQUIRE_THROWS(
        MaterialSkeleton<std::string::iterator> mSkel(begin, end, LN) );

    }

  } // GIVEN
} // SCENARIO

