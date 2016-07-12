#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "HeadRecord Tests";
  LOG(INFO) << "======================";  
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "HeadRecord Complete!";
  return result;
}

using namespace ENDFtk::implementation;

SCENARIO( "HeadRecord Tests", "[ENDFtk], [HeadRecord]" ){
  GIVEN( "a section division which is a head" ){
    std::string line =
      " 1.001000+3 9.991673-1          0          1          2          5 125 1451    1";
    auto lineNumber = 0l;
    auto it = line.begin();
    auto end = line.end();
    auto record = StructureDivision( it, end, lineNumber );
    REQUIRE( record.isHead() );
    THEN("asHead will not throw"){
      REQUIRE_NOTHROW( asHead( record ) );
      REQUIRE_NOTHROW( asHead( 1001.0, 0.9991673, record ) );
      REQUIRE_NOTHROW( asHead( 1000.0, 0.9991673, record ) ); /* only warns */
      REQUIRE_NOTHROW( asHead( 1001.0, 0.9981673, record ) );
    }
    THEN("a mutable head reference can be made"){
      HeadRecord& head = asHead( record );
      THEN("the getters work"){
        REQUIRE( 1001.0 == head.ZA() );
        REQUIRE( 0.9991673 == head.AWR() );
        REQUIRE( 0.9991673 == head.atomicWeightRatio() );
        REQUIRE( 0 == head.L1() );
        REQUIRE( 1 == head.L2() );
        REQUIRE( 2 == head.N1() );
        REQUIRE( 5 == head.N2() );
        REQUIRE( 125 == head.MAT() );
        REQUIRE( 125 == head.material() );
        REQUIRE( 1 == head.MF() );
        REQUIRE( 1 == head.file() );
        REQUIRE( 451 == head.MT() );
        REQUIRE( 451 == head.section() );
      }
    }
    THEN("a immutable head reference can be made"){
      const auto& constRecord = record;
      const HeadRecord& head = asHead( constRecord );
      THEN("the getters work"){
        REQUIRE( 1001.0 == head.ZA() );
        REQUIRE( 0.9991673 == head.AWR() );
        REQUIRE( 0.9991673 == head.atomicWeightRatio() );
        REQUIRE( 0 == head.L1() );
        REQUIRE( 1 == head.L2() );
        REQUIRE( 2 == head.N1() );
        REQUIRE( 5 == head.N2() );
        REQUIRE( 125 == head.MAT() );
        REQUIRE( 125 == head.material() );
        REQUIRE( 1 == head.MF() );
        REQUIRE( 1 == head.file() );
        REQUIRE( 451 == head.MT() );
        REQUIRE( 451 == head.section() );
      }
    }
  }
}
