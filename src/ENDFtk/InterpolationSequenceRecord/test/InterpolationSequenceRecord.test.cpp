#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();

bool compareControlRecords( const ControlRecord& left,
                            const ControlRecord& right ) {

    return ( left.C1() < right.C1() );
}

namespace njoy {

  namespace ENDFtk {

    template<> void
    validateSequence< ControlRecord >( const std::vector< ControlRecord >& seq ) {

      auto iter = std::is_sorted_until( seq.begin(), seq.end(),
                                        &compareControlRecords );
      const bool areSorted = ( iter == seq.end() );

      if ( not areSorted ){
        Log::error( "Sequence is not sorted" );
        const auto position = iter - seq.begin();
        Log::info( "sequence[{}]: {}", (position - 1), iter[-1].C1() );
        Log::info( "sequence[{}]: {}", position, iter[0].C1() );
        throw std::exception();
      }
    }
  }
}
  
SCENARIO( "InterpolationSequenceRecord" ) {

  GIVEN( "valid data for an InterpolationSequenceRecord" ) {

    InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
    std::vector< ControlRecord > sequence = {
        ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
        ControlRecord( 14.0, 15.0, 16, 17, 18, 19 ) };

    THEN( "an InterpolationSequenceRecord can be constructed "
          "and its members can be tested" ) {

      InterpolationSequenceRecord< ControlRecord >
        chunk( std::move( interpolation ), std::move( sequence ) );

      REQUIRE( 4 == chunk.NC() );

      InterpolationRecord tab2 = chunk.tab2();
      auto interpolants = tab2.interpolants();
      auto boundaries = tab2.boundaries();
      auto records = chunk.records();

      REQUIRE( 3. == Approx( tab2.C1() ) );
      REQUIRE( 5. == Approx( tab2.C2() ) );
      REQUIRE( 6 == tab2.L1() );
      REQUIRE( 7 == tab2.L2() );
      REQUIRE( 1 == tab2.NR() );
      REQUIRE( 2 == tab2.NZ() );
      REQUIRE( 1 == interpolants.size() );
      REQUIRE( 1 == boundaries.size() );
      REQUIRE( 4 == interpolants[0] );
      REQUIRE( 2 == boundaries[0] );

      REQUIRE( 2 == records.size() );
      REQUIRE( 8. == Approx( records[0].C1() ) );
      REQUIRE( 9. == Approx( records[0].C2() ) );
      REQUIRE( 10 == records[0].L1() );
      REQUIRE( 11 == records[0].L2() );
      REQUIRE( 12 == records[0].N1() );
      REQUIRE( 13 == records[0].N2() );
      REQUIRE( 14. == Approx( records[1].C1() ) );
      REQUIRE( 15. == Approx( records[1].C2() ) );
      REQUIRE( 16 == records[1].L1() );
      REQUIRE( 17 == records[1].L2() );
      REQUIRE( 18 == records[1].N1() );
      REQUIRE( 19 == records[1].N2() );
    }
  }

  GIVEN( "a string representation of a valid InterpolationSequenceRecord "
          "and its members can be tested" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "an InterpolationSequenceRecord can be constructed" ) {
      InterpolationSequenceRecord< ControlRecord >
        chunk( begin, end, lineNumber, 9228, 1, 455 );

      REQUIRE( 4 == chunk.NC() );

      InterpolationRecord tab2 = chunk.tab2();
      auto interpolants = tab2.interpolants();
      auto boundaries = tab2.boundaries();
      auto records = chunk.records();

      REQUIRE( 3. == Approx( tab2.C1() ) );
      REQUIRE( 5. == Approx( tab2.C2() ) );
      REQUIRE( 6 == tab2.L1() );
      REQUIRE( 7 == tab2.L2() );
      REQUIRE( 1 == tab2.NR() );
      REQUIRE( 2 == tab2.NZ() );
      REQUIRE( 1 == interpolants.size() );
      REQUIRE( 1 == boundaries.size() );
      REQUIRE( 4 == interpolants[0] );
      REQUIRE( 2 == boundaries[0] );

      REQUIRE( 2 == records.size() );
      REQUIRE( 8. == Approx( records[0].C1() ) );
      REQUIRE( 9. == Approx( records[0].C2() ) );
      REQUIRE( 10 == records[0].L1() );
      REQUIRE( 11 == records[0].L2() );
      REQUIRE( 12 == records[0].N1() );
      REQUIRE( 13 == records[0].N2() );
      REQUIRE( 14. == Approx( records[1].C1() ) );
      REQUIRE( 15. == Approx( records[1].C2() ) );
      REQUIRE( 16 == records[1].L1() );
      REQUIRE( 17 == records[1].L2() );
      REQUIRE( 18 == records[1].N1() );
      REQUIRE( 19 == records[1].N2() );
    }
  } // GIVEN

  GIVEN( "invalid data for an InterpolationSequenceRecord" ) {

    InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
    std::vector< ControlRecord > sequence = {
        ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
        ControlRecord( 7.0, 15.0, 16, 17, 18, 19 ) };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( InterpolationSequenceRecord< ControlRecord >( std::move( interpolation ), std::move( sequence ) ) );
    }
  }

  GIVEN( "inconsistent NZ and data points" ) {

    InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
    std::vector< ControlRecord > sequence = {
        ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
        ControlRecord( 7.0, 15.0, 16, 17, 18, 19 ),
        ControlRecord( 20.0, 21.0, 22, 23, 24, 25 ) };

    THEN( "an exception is thrown" ) {

      REQUIRE_THROWS( InterpolationSequenceRecord< ControlRecord >( std::move( interpolation ), std::move( sequence ) ) );
    }
  }

  GIVEN( "a valid instance of InterpolationSequenceRecord" ) {
    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1; 
    InterpolationSequenceRecord< ControlRecord >
      chunk( begin, end, lineNumber, 9228, 1, 455 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9228, 1, 455 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 3.000000+0 5.000000+0          6          7          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 8.000000+0 9.000000+0         10         11         12         139228 1455     \n"
    " 1.400000+1 1.500000+1         16         17         18         199228 1455     \n";
}

