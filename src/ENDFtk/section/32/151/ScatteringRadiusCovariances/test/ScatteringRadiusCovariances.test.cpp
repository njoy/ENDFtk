#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ScatteringRadiusCovariances = section::Type< 32, 151 >::ScatteringRadiusCovariances;
using SquareMatrix = section::SquareMatrix;
using RectangularMatrix = section::RectangularMatrix;
using CovariancePairs = section::CovariancePairs;
using ExplicitCovariance = section::ExplicitCovariance;

std::string chunk();
void verifyChunk( const ScatteringRadiusCovariances& );

SCENARIO( "ScatteringRadiusCovariances" ) {

  GIVEN( "valid data for a ScatteringRadiusCovariances" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > rowEnergies = { 1.1, 1.2, 1.3 };
      std::vector< double > columnEnergies = { 2.1, 2.2, 2.3, 2.4 };
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > energies = { 0, 100, 200 };
      std::vector< double > svalues = { 1, 2, 3, 4 };

      std::vector< ExplicitCovariance > ni = {
        SquareMatrix( 0, std::move(energies), std::move(svalues) ),
        RectangularMatrix( std::move(rowEnergies),
                           std::move(columnEnergies),
                           std::move(values) ),
        CovariancePairs( 1, { 1., 3. }, { 2., 4. } ) };

      auto chunk = ScatteringRadiusCovariances( std::move( ni ) );

      THEN( "a ScatteringRadiusCovariances can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 32, 151 );
        CHECK( buffer == string );
      } // THEN

    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ScatteringRadiusCovariances chunk( begin, end, lineNumber, 9437, 32, 151 );

      THEN( "a ScatteringRadiusCovariances object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9437, 32, 151 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 0.000000+0 0.000000+0          0          0          0          3943732151     \n"
    " 0.000000+0 0.000000+0          0          5          7          3943732151     \n"
    " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943732151     \n"
    " 4.000000+0                                                       943732151     \n"
    " 0.000000+0 0.000000+0          0          6         13          3943732151     \n"
    " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0943732151     \n"
    " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0943732151     \n"
    " 6.000000+0                                                       943732151     \n"
    " 0.000000+0 0.000000+0          0          1          4          2943732151     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      943732151     \n";
}

void verifyChunk( const ScatteringRadiusCovariances& chunk ) {

  CHECK( 3 == chunk.NI() );
  CHECK( 3 == chunk.numberDataBlocks() );
  CHECK( 3 == chunk.data().size() );

  auto stuff = std::get< SquareMatrix >( chunk.data()[0] );

  // metadata
  CHECK( 0 == stuff.LS() );
  CHECK( 0 == stuff.symmetryFlag() );
  CHECK( !stuff.isSymmetric() );
  CHECK( 5 == stuff.LB() );
  CHECK( 5 == stuff.procedure() );
  CHECK( 7 == stuff.NT() );
  CHECK( 7 == stuff.numberValues() );
  CHECK( 3 == stuff.NE() );
  CHECK( 3 == stuff.numberEnergies() );

  // values
  CHECK( 0. == Approx( stuff.energies()[0] ) );
  CHECK( 100. == Approx( stuff.energies()[1] ) );
  CHECK( 200. == Approx( stuff.energies()[2] ) );
  CHECK( 1. == Approx( stuff.values()[0] ) );
  CHECK( 2. == Approx( stuff.values()[1] ) );
  CHECK( 3. == Approx( stuff.values()[2] ) );
  CHECK( 4. == Approx( stuff.values()[3] ) );

  CHECK( 10 == chunk.NC() );
}
