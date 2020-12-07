#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using PolynomialMultiplicity = section::PolynomialMultiplicity;

std::string chunk();
void verifyChunk( const PolynomialMultiplicity& );
std::string invalidChunk();

SCENARIO( "PolynomialMultiplicity" ) {

  GIVEN( "valid data for a TabulatedMultiplicity" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 2.4367, 5e-2 };

      PolynomialMultiplicity chunk( std::move( coefficients ) );

      THEN( "an PolynomialMultiplicity can be constructed and members can be "
            "tested" ) {

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

      PolynomialMultiplicity chunk( begin, end, lineNumber, 9228, 1, 455 );

      THEN( "a PolynomialMultiplicity can be constructed and members can be "
            "tested" ) {

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

  GIVEN( "invalid data for a PolynomialMultiplicity" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialMultiplicity( begin, end, lineNumber,
                                             9228, 1, 455 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          2          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}

void verifyChunk( const PolynomialMultiplicity& chunk ) {

  CHECK( 1 == chunk.LNU() );
  CHECK( 1 == chunk.representation() );

  CHECK( 2 == chunk.NCO() );
  CHECK( 2 == chunk.numberCoefficients() );
  CHECK( 2 == chunk.C().size() );
  CHECK( 2 == chunk.coefficients().size() );
  CHECK( 2.4367 == Approx( chunk.C()[0] ) );
  CHECK( 5e-2 == Approx( chunk.C()[1] ) );
  CHECK( 2.4367 == Approx( chunk.coefficients()[0] ) );
  CHECK( 5e-2 == Approx( chunk.coefficients()[1] ) );

  CHECK( 2 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          09228 1455     \n"
    " 2.436700+0 5.000000-2                                            9228 1455     \n";
}
