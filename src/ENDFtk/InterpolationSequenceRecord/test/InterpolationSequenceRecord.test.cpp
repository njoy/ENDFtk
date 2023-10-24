// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/InterpolationSequenceRecord.hpp"

// other includes
#include "ENDFtk/ControlRecord.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk();
void verifyChunk( const InterpolationSequenceRecord< ControlRecord >& );

bool compareControlRecords( const ControlRecord& left,
                            const ControlRecord& right ) {

    return ( left.C1() < right.C1() );
}

namespace njoy {
namespace ENDFtk {

  template<> void
  validateSequence< ControlRecord >(
    const std::vector< ControlRecord >& seq ) {

    auto iter = std::is_sorted_until( seq.begin(), seq.end(),
                                      &compareControlRecords );
    const bool areSorted = ( iter == seq.end() );
    if ( not areSorted ) {

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

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
      std::vector< ControlRecord > sequence = {
          ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
          ControlRecord( 14.0, 15.0, 16, 17, 18, 19 ) };

      InterpolationSequenceRecord< ControlRecord >
        chunk( std::move( interpolation ), std::move( sequence ) );

      THEN( "an InterpolationSequenceRecord can be constructed "
            "and its members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      InterpolationSequenceRecord< ControlRecord > chunk =
        readInterpolationSequenceRecord< ControlRecord >( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "an InterpolationSequenceRecord can be constructed "
            "and its members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 1, 455 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationSequenceRecord" ) {

    WHEN( "the CONT records are not sorted" ) {

      InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
      std::vector< ControlRecord > sequence = {
          ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
          ControlRecord( 7.0, 15.0, 16, 17, 18, 19 ) };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          InterpolationSequenceRecord< ControlRecord >(
            std::move( interpolation ), std::move( sequence ) ) );
      } // THEN
    } // WHEN

    WHEN( "inconsistent NZ and data points are used" ) {

      InterpolationRecord interpolation( 3.0, 5.0, 6, 7, { 2 }, { 4 } );
      std::vector< ControlRecord > sequence = {
          ControlRecord( 8.0, 9.0, 10, 11, 12, 13 ),
          ControlRecord( 7.0, 15.0, 16, 17, 18, 19 ),
          ControlRecord( 20.0, 21.0, 22, 23, 24, 25 ) };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          InterpolationSequenceRecord< ControlRecord >(
            std::move( interpolation ), std::move( sequence ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 3.000000+0 5.000000+0          6          7          1          29228 1455     \n"
    "          2          4                                            9228 1455     \n"
    " 8.000000+0 9.000000+0         10         11         12         139228 1455     \n"
    " 1.400000+1 1.500000+1         16         17         18         199228 1455     \n";
}

void verifyChunk( const InterpolationSequenceRecord< ControlRecord >& chunk ) {

  CHECK( 4 == chunk.NC() );

  InterpolationRecord tab2 = chunk.tab2();
  auto interpolants = tab2.interpolants();
  auto boundaries = tab2.boundaries();
  auto records = chunk.records();

  CHECK_THAT( 3., WithinRel( tab2.C1() ) );
  CHECK_THAT( 5., WithinRel( tab2.C2() ) );
  CHECK( 6 == tab2.L1() );
  CHECK( 7 == tab2.L2() );
  CHECK( 1 == tab2.NR() );
  CHECK( 2 == tab2.NZ() );
  CHECK( 1 == interpolants.size() );
  CHECK( 1 == boundaries.size() );
  CHECK( 4 == interpolants[0] );
  CHECK( 2 == boundaries[0] );

  CHECK( 2 == records.size() );
  CHECK_THAT( 8., WithinRel( records[0].C1() ) );
  CHECK_THAT( 9., WithinRel( records[0].C2() ) );
  CHECK( 10 == records[0].L1() );
  CHECK( 11 == records[0].L2() );
  CHECK( 12 == records[0].N1() );
  CHECK( 13 == records[0].N2() );
  CHECK_THAT( 14., WithinRel( records[1].C1() ) );
  CHECK_THAT( 15., WithinRel( records[1].C2() ) );
  CHECK( 16 == records[1].L1() );
  CHECK( 17 == records[1].L2() );
  CHECK( 18 == records[1].N1() );
  CHECK( 19 == records[1].N2() );
}
