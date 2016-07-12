#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "ControlRecord Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "ControlRecord Complete!";
  return result;
}

using namespace ENDFtk::implementation;

SCENARIO( "ControlRecord Tests", "[ENDFtk], [ControlRecord]" ){
  std::string line =
    " 1.001000+3 9.991673-1          0          0          0          5 125 1451    1\n";

  auto values = std::make_tuple( 1.001000E+3, 9.991673E-1, 0, 0, 0, 5 );

  GIVEN( "value construction, the ctor works"){
    REQUIRE_NOTHROW(
      ControlRecord( std::get< 0 >(values), std::get< 1 >(values),
                     std::get< 2 >(values), std::get< 3 >(values),
                     std::get< 4 >(values), std::get< 5 >(values) ) );
  }
  GIVEN( "iterators and a line number"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    WHEN("the tail values match, the ctor works"){
      REQUIRE_NOTHROW( ControlRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("the MAT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ControlRecord( it, end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("the MF value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ControlRecord( it, end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("the MT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ControlRecord( it, end, lineNumber, 125, 1, 452 ) );
    }
  }
  GIVEN( "A constructed control record"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    auto controlRecord0 = ControlRecord( it, end, lineNumber, 125, 1, 451 );
    const auto& constControlRecord0 = controlRecord0;
    auto controlRecord1 =
      ControlRecord( std::get< 0 >(values), std::get< 1 >(values),
                     std::get< 2 >(values), std::get< 3 >(values),
                     std::get< 4 >(values), std::get< 5 >(values) );
    const auto& constControlRecord1 = controlRecord1;
    THEN( "the getter will work" ){
      REQUIRE( controlRecord0.C1() == std::get< 0 >( values ) );
      REQUIRE( controlRecord1.C1() == std::get< 0 >( values ) );
      REQUIRE( constControlRecord0.C1() == std::get< 0 >( values ) );
      REQUIRE( constControlRecord1.C1() == std::get< 0 >( values ) );
      REQUIRE( controlRecord0.C2() == std::get< 1 >( values ) );
      REQUIRE( controlRecord1.C2() == std::get< 1 >( values ) );
      REQUIRE( constControlRecord0.C2() == std::get< 1 >( values ) );
      REQUIRE( constControlRecord1.C2() == std::get< 1 >( values ) );
      REQUIRE( controlRecord0.L1() == std::get< 2 >( values ) );
      REQUIRE( controlRecord1.L1() == std::get< 2 >( values ) );
      REQUIRE( constControlRecord0.L1() == std::get< 2 >( values ) );
      REQUIRE( constControlRecord1.L1() == std::get< 2 >( values ) );
      REQUIRE( controlRecord0.L2() == std::get< 3 >( values ) );
      REQUIRE( controlRecord1.L2() == std::get< 3 >( values ) );
      REQUIRE( constControlRecord0.L2() == std::get< 3 >( values ) );
      REQUIRE( constControlRecord1.L2() == std::get< 3 >( values ) );
      REQUIRE( controlRecord0.N1() == std::get< 4 >( values ) );
      REQUIRE( controlRecord1.N1() == std::get< 4 >( values ) );
      REQUIRE( constControlRecord0.N1() == std::get< 4 >( values ) );
      REQUIRE( constControlRecord1.N1() == std::get< 4 >( values ) );
      REQUIRE( controlRecord0.N2() == std::get< 5 >( values ) );
      REQUIRE( controlRecord1.N2() == std::get< 5 >( values ) );
      REQUIRE( constControlRecord0.N2() == std::get< 5 >( values ) );
      REQUIRE( constControlRecord1.N2() == std::get< 5 >( values ) );
      
      controlRecord0.C1() = 3.14;
      REQUIRE( controlRecord0.C1() == 3.14 );
      controlRecord0.C2() = 2.5;
      REQUIRE( controlRecord0.C2() == 2.5 );
      controlRecord0.L1() = 5;
      REQUIRE( controlRecord0.L1() == 5 );
      controlRecord0.L2() = 6;
      REQUIRE( controlRecord0.L2() == 6 );
      controlRecord0.N1() = 7;
      REQUIRE( controlRecord0.N1() == 7 );
      controlRecord0.N2() = 8;
      REQUIRE( controlRecord0.N2() == 8 );
      // can't assign to const instances. doesn't compile
      // constControlRecord0.N1() = 10;
    }
    THEN( "the equality and inequality operators will work" ){
      REQUIRE( controlRecord0 == controlRecord1 );
      controlRecord0.N1() = 10;
      controlRecord1.N1() = 8;
      REQUIRE( controlRecord0 != controlRecord1 );
    }
  }
}
