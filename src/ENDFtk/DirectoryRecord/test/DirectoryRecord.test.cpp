#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "DirectoryRecord Tests", "[ENDFtk], [DirectoryRecord]" ){
  std::string line =
    "                                1        451        101          5 125 1451     \n";

  auto values = std::make_tuple( 1, 451, 101, 5 );
  GIVEN( "value construction, the ctor works"){
    REQUIRE_NOTHROW(
      DirectoryRecord( std::get< 0 >(values), std::get< 1 >(values),
                     std::get< 2 >(values), std::get< 3 >(values) ) );
  }
  
  GIVEN( "iterators and a line number"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    WHEN("the tail values match, the ctor works"){
      REQUIRE_NOTHROW( DirectoryRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
    WHEN("the MAT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( DirectoryRecord( it, end, lineNumber, 126, 1, 451 ) );
    }
    WHEN("the MF value doesn't match, the ctor throws"){
      REQUIRE_THROWS( DirectoryRecord( it, end, lineNumber, 125, 2, 451 ) );
    }
    WHEN("the MT value doesn't match, the ctor throws"){
      REQUIRE_THROWS( DirectoryRecord( it, end, lineNumber, 125, 1, 452 ) );
    }
  }
  
  SECTION("print"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;

    std::string buffer;
    auto output = std::back_inserter( buffer );
    
    const auto dir = DirectoryRecord( it, end, lineNumber, 125, 1, 451 );
    dir.print( output, 125, 1, 451 );

    REQUIRE( buffer == line );
  }

  SECTION("NC"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    
    REQUIRE( 1 == DirectoryRecord( it, end, lineNumber, 125, 1, 451 ).NC() );
  }

  
  GIVEN( "A constructed directory record"){
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    auto directoryRecord0 = DirectoryRecord( it, end, lineNumber, 125, 1, 451 );
    const auto& constDirectoryRecord0 = directoryRecord0;
    auto directoryRecord1 =
      DirectoryRecord( std::get< 0 >(values), std::get< 1 >(values),
                       std::get< 2 >(values), std::get< 3 >(values) );
    const auto& constDirectoryRecord1 = directoryRecord1;
    THEN( "the getter will work" ){
      REQUIRE( directoryRecord0.L1() == std::get< 0 >( values ) );
      REQUIRE( directoryRecord1.L1() == std::get< 0 >( values ) );
      REQUIRE( constDirectoryRecord0.L1() == std::get< 0 >( values ) );
      REQUIRE( constDirectoryRecord1.L1() == std::get< 0 >( values ) );
      REQUIRE( directoryRecord0.L2() == std::get< 1 >( values ) );
      REQUIRE( directoryRecord1.L2() == std::get< 1 >( values ) );
      REQUIRE( constDirectoryRecord0.L2() == std::get< 1 >( values ) );
      REQUIRE( constDirectoryRecord1.L2() == std::get< 1 >( values ) );
      REQUIRE( directoryRecord0.N1() == std::get< 2 >( values ) );
      REQUIRE( directoryRecord1.N1() == std::get< 2 >( values ) );
      REQUIRE( constDirectoryRecord0.N1() == std::get< 2 >( values ) );
      REQUIRE( constDirectoryRecord1.N1() == std::get< 2 >( values ) );
      REQUIRE( directoryRecord0.N2() == std::get< 3 >( values ) );
      REQUIRE( directoryRecord1.N2() == std::get< 3 >( values ) );
      REQUIRE( constDirectoryRecord0.N2() == std::get< 3 >( values ) );
      REQUIRE( constDirectoryRecord1.N2() == std::get< 3 >( values ) );

      directoryRecord0.L1() = 5;
      REQUIRE( directoryRecord0.L1() == 5 );
      directoryRecord0.L2() = 6;
      REQUIRE( directoryRecord0.L2() == 6 );
      directoryRecord0.N1() = 7;
      REQUIRE( directoryRecord0.N1() == 7 );
      directoryRecord0.N2() = 8;
      REQUIRE( directoryRecord0.N2() == 8 );
      // can't assign to const instances. doesn't compile
      // constDirectoryRecord0.N1() = 10;
    }
    THEN( "the equality and inequality operators will work" ){
      REQUIRE( directoryRecord0 == directoryRecord1 );
      directoryRecord0.N1() = 10;
      directoryRecord1.N1() = 8;
      REQUIRE( directoryRecord0 != directoryRecord1 );
    }
  }
  GIVEN("A line with a typo"){
    std::string line =
      "                                1        451        101          5 125 14a1   92\n";
    auto it = line.begin();
    auto end = line.end();
    auto lineNumber = 0l;
    
    THEN("the ctor throws"){
      REQUIRE_THROWS( DirectoryRecord( it, end, lineNumber, 125, 1, 451 ) );
    }
  }
}
