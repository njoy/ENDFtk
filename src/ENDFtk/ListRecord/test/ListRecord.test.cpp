#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/ListRecord.hpp"

// other includes
#include "header-utilities/copy.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

SCENARIO( "ListRecord Tests", "[ENDFtk], [ListRecord]" ){
  auto values = std::make_tuple( 1.001000E+3, 9.991673E-1, 0, 0, 10, 5 );
  std::vector< double > list{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  std::string lines =
    " 1.001000+3 9.991673-1          0          0         10          5 125 1451     \n"
    " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451     \n"
    " 6.000000+0 7.000000+0 8.000000+0 9.000000+0                       125 1451     \n";

  GIVEN( "value construction, the ctor works"){
    REQUIRE_NOTHROW(
      ListRecord( std::get< 0 >(values), std::get< 1 >(values),
                  std::get< 2 >(values), std::get< 3 >(values),
                  std::get< 5 >(values), njoy::utility::copy(list) ) );
  }

  GIVEN( "iterators and a line number"){
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;

    WHEN("the tail values match, the ctor works"){
      REQUIRE_NOTHROW( ListRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("the MAT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ListRecord( it, end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("the MF value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ListRecord( it, end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("the MT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( ListRecord( it, end, lineNumber, 125, 1, 452 ) );
    }
  }

  SECTION( "print" ){
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;

    int MAT = 125;
    int MF = 1;
    int MT = 451;

    const auto list = ListRecord( it, end, lineNumber, 125, 1, 451 );
    std::string buffer;
    auto output = std::back_inserter( buffer );
    list.print( output, MAT, MF, MT );

    REQUIRE( buffer == lines );
  }

    SECTION( "print" ){
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;

    int MAT = 125;
    int MF = 1;
    int MT = 451;

    const auto list = ListRecord( it, end, lineNumber, 125, 1, 451 );
    REQUIRE( list.NC() == 3 );
  }

  GIVEN("nonzero entries outside list range"){
    std::string lines =
      " 1.001000+3 9.991673-1          0          0         10          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1 0.000000+0 125 1451    3\n";
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;
    THEN("the ctor throws"){
      REQUIRE_THROWS( ListRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
  }
  GIVEN("blanks in zero entries"){
    std::string lines =
      " 1.001000+3 9.991673-1          0          0         10          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0                       125 1451    3\n";
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;
    THEN("the ctor succeeds"){
      REQUIRE_NOTHROW( ListRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
  }
  GIVEN( "A constructed list record"){
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;
    auto listRecord0 = ListRecord( it, end, lineNumber, 125, 1, 451 );
    const auto& constListRecord0 = listRecord0;
    auto listRecord1 =
      ListRecord( std::get< 0 >(values), std::get< 1 >(values),
                  std::get< 2 >(values), std::get< 3 >(values),
                  std::get< 5 >(values), njoy::utility::copy(list) );

    const auto& constListRecord1 = listRecord1;
    THEN( "the getter will work" ){
      REQUIRE( listRecord0.C1() == std::get< 0 >( values ) );
      REQUIRE( listRecord1.C1() == std::get< 0 >( values ) );
      REQUIRE( constListRecord0.C1() == std::get< 0 >( values ) );
      REQUIRE( constListRecord1.C1() == std::get< 0 >( values ) );
      REQUIRE( listRecord0.C2() == std::get< 1 >( values ) );
      REQUIRE( listRecord1.C2() == std::get< 1 >( values ) );
      REQUIRE( constListRecord0.C2() == std::get< 1 >( values ) );
      REQUIRE( constListRecord1.C2() == std::get< 1 >( values ) );
      REQUIRE( listRecord0.L1() == std::get< 2 >( values ) );
      REQUIRE( listRecord1.L1() == std::get< 2 >( values ) );
      REQUIRE( constListRecord0.L1() == std::get< 2 >( values ) );
      REQUIRE( constListRecord1.L1() == std::get< 2 >( values ) );
      REQUIRE( listRecord0.L2() == std::get< 3 >( values ) );
      REQUIRE( listRecord1.L2() == std::get< 3 >( values ) );
      REQUIRE( constListRecord0.L2() == std::get< 3 >( values ) );
      REQUIRE( constListRecord1.L2() == std::get< 3 >( values ) );
      REQUIRE( long(listRecord0.NPL()) == std::get< 4 >( values ) );
      REQUIRE( long(listRecord1.NPL()) == std::get< 4 >( values ) );
      REQUIRE( long(constListRecord0.NPL()) == std::get< 4 >( values ) );
      REQUIRE( long(constListRecord1.NPL()) == std::get< 4 >( values ) );
      REQUIRE( listRecord0.N2() == std::get< 5 >( values ) );
      REQUIRE( listRecord1.N2() == std::get< 5 >( values ) );
      REQUIRE( constListRecord0.N2() == std::get< 5 >( values ) );
      REQUIRE( constListRecord1.N2() == std::get< 5 >( values ) );

      auto B = listRecord0.B();
      REQUIRE( std::equal( B.begin(), B.end(), list.begin(), list.end() ) );
    }
    THEN( "the equality and inequality operators will work" ){
      REQUIRE( listRecord0 == listRecord1 );
      REQUIRE( listRecord0 == constListRecord1 );
      listRecord0.N2() = 10;
      REQUIRE( listRecord0 != listRecord1 );
      REQUIRE( listRecord0 != constListRecord1 );
    }
  }
  GIVEN("A LIST record with a negative NPL value"){
    std::string lines =
      " 1.001000+3 9.991673-1          0          0         -5          5 125 1451    1\n"
      " 0.000000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 125 1451    2\n"
      " 6.000000+0 7.000000+0 8.000000+0 9.000000+0 0.000000+0 0.000000+0 125 1451    3\n";
    auto it = lines.begin();
    auto end = lines.end();
    auto lineNumber = 0l;
    THEN("the ctor throws"){
      REQUIRE_THROWS( ListRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
  }
}
