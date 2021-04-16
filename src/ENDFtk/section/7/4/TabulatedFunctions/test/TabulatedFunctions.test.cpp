#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using TabulatedFunctions = section::Type< 7, 4 >::TabulatedFunctions;
using ScatteringFunction = section::Type< 7, 4 >::TabulatedFunctions::ScatteringFunction;

std::string chunkWithOneTemperature();
void verifyChunkWithOneTemperature( const TabulatedFunctions& );
std::string invalidLT();

SCENARIO( "TabulatedFunctions" ) {

  GIVEN( "valid data for a TabulatedFunctions thermal scattering law with one "
         "temperature" ) {

    std::string string = chunkWithOneTemperature();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 4 };
      std::vector< ScatteringFunction > betas = {
          ScatteringFunction(
                     293.6, 0.0, { 5 }, { 4 },
                     { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                       8.847604e+1 },
                     { 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                       5.29573e-10 } ),
          ScatteringFunction(
                     293.6, 3.952570e-2, { 5 }, { 2 },
                     { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                       8.847604e+1 },
                     { 2.386694e-4, 2.508273e-4, 2.636238e-4, 2.770291e-4,
                       2.911373e-4 } ) };

      TabulatedFunctions chunk( std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( betas ) );

      THEN( "a TabulatedFunctions can be constructed using a TabulationRecord" ) {

        verifyChunkWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      TabulatedFunctions chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a TabulatedFunctions can  be constructed and members can be tested" ) {

        verifyChunkWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "something is wrong with the interpolation sequence record" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        std::vector< long > wrongBoundaries = { 2, 4 }; // one more
        std::vector< long > interpolants = { 4 };
        std::vector< ScatteringFunction > betas = {
            ScatteringFunction(
                       293.6, 0.0, { 5 }, { 4 },
                       { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                         8.847604e+1 },
                       { 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                         5.29573e-10 } ),
            ScatteringFunction(
                       293.6, 3.952570e-2, { 5 }, { 2 },
                       { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                         8.847604e+1 },
                       { 2.386694e-4, 2.508273e-4, 2.636238e-4, 2.770291e-4,
                         2.911373e-4 } ) };

        CHECK_THROWS( TabulatedFunctions( std::move( wrongBoundaries ),
                                          std::move( interpolants ),
                                          std::move( betas ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > wrongInterpolants = { 4, 2 }; // one more
        std::vector< ScatteringFunction > betas = {
            ScatteringFunction(
                       293.6, 0.0, { 5 }, { 4 },
                       { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                         8.847604e+1 },
                       { 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                         5.29573e-10 } ),
            ScatteringFunction(
                       293.6, 3.952570e-2, { 5 }, { 2 },
                       { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                         8.847604e+1 },
                       { 2.386694e-4, 2.508273e-4, 2.636238e-4, 2.770291e-4,
                         2.911373e-4 } ) };

        CHECK_THROWS( TabulatedFunctions( std::move( boundaries ),
                                          std::move( wrongInterpolants ),
                                          std::move( betas ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the sequence" ) {

        std::vector< long > boundaries = { 2 };
        std::vector< long > interpolants = { 4 };
        std::vector< ScatteringFunction > wrongBetas = {
            ScatteringFunction(
                       293.6, 0.0, { 5 }, { 4 },
                       { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                         8.847604e+1 },
                       { 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                         5.29573e-10 } ) }; // one less

        CHECK_THROWS( TabulatedFunctions( std::move( boundaries ),
                                          std::move( interpolants ),
                                          std::move( wrongBetas ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a TabulatedFunctions thermal scattering law"
           " with an invalid LT is used" ) {

      std::string string = invalidLT();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        CHECK_THROWS( TabulatedFunctions( begin, end, lineNumber, 27, 7, 4 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOneTemperature() {
  return
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n";
}

void verifyChunkWithOneTemperature( const TabulatedFunctions& chunk ) {

  CHECK( 1 == chunk.NR() );
  CHECK( 2 == chunk.NB() );
  CHECK( 2 == chunk.numberBetas() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 4 == chunk.interpolants()[0] );

  auto value = chunk.scatteringFunctions()[0];
  CHECK( 0.0 == Approx( value.beta() ) );
  CHECK( 0 == value.LT() );
  CHECK( 0 == value.temperatureDependenceFlag() );
  CHECK( 1 == value.NT() );
  CHECK( 1 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NP() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 4 == value.interpolants()[0] );

  CHECK( 1 == value.T().size() );
  CHECK( 1 == value.temperatures().size() );
  CHECK( 293.6 == Approx( value.T()[0] ) );
  CHECK( 293.6 == Approx( value.temperatures()[0] ) );

  CHECK( 5 == value.A().size() );
  CHECK( 5 == value.alphas().size() );
  CHECK( 4.423802e-3 == Approx( value.A()[0] ) );
  CHECK( 4.649528e-3 == Approx( value.A()[1] ) );
  CHECK( 4.886772e-3 == Approx( value.A()[2] ) );
  CHECK( 8.418068e+1 == Approx( value.A()[3] ) );
  CHECK( 8.847604e+1 == Approx( value.A()[4] ) );
  CHECK( 4.423802e-3 == Approx( value.alphas()[0] ) );
  CHECK( 4.649528e-3 == Approx( value.alphas()[1] ) );
  CHECK( 4.886772e-3 == Approx( value.alphas()[2] ) );
  CHECK( 8.418068e+1 == Approx( value.alphas()[3] ) );
  CHECK( 8.847604e+1 == Approx( value.alphas()[4] ) );

  CHECK( 0 == value.LI().size() );
  CHECK( 0 == value.temperatureInterpolants().size() );

  decltype(auto) values = value.S();
  CHECK( 1 == values.size() );
  CHECK( 5 == values[0].size() );
  CHECK( 2.386876e-4 == Approx( values[0][0] ) );
  CHECK( 2.508466e-4 == Approx( values[0][1] ) );
  CHECK( 2.636238e-4 == Approx( values[0][2] ) );
  CHECK( 1.306574e-9 == Approx( values[0][3] ) );
  CHECK( 5.29573e-10 == Approx( values[0][4] ) );

  values = value.thermalScatteringValues();
  CHECK( 1 == values.size() );
  CHECK( 5 == values[0].size() );
  CHECK( 2.386876e-4 == Approx( values[0][0] ) );
  CHECK( 2.508466e-4 == Approx( values[0][1] ) );
  CHECK( 2.636238e-4 == Approx( values[0][2] ) );
  CHECK( 1.306574e-9 == Approx( values[0][3] ) );
  CHECK( 5.29573e-10 == Approx( values[0][4] ) );

  value = chunk.scatteringFunctions()[1];
  CHECK( 3.952570e-2 == Approx( value.beta() ) );
  CHECK( 0 == value.LT() );
  CHECK( 0 == value.temperatureDependenceFlag() );
  CHECK( 1 == value.NT() );
  CHECK( 1 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.NP() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 2 == value.interpolants()[0] );

  CHECK( 1 == value.T().size() );
  CHECK( 1 == value.temperatures().size() );
  CHECK( 293.6 == Approx( value.T()[0] ) );
  CHECK( 293.6 == Approx( value.temperatures()[0] ) );

  CHECK( 5 == value.A().size() );
  CHECK( 5 == value.alphas().size() );
  CHECK( 4.423802e-3 == Approx( value.A()[0] ) );
  CHECK( 4.649528e-3 == Approx( value.A()[1] ) );
  CHECK( 4.886772e-3 == Approx( value.A()[2] ) );
  CHECK( 8.418068e+1 == Approx( value.A()[3] ) );
  CHECK( 8.847604e+1 == Approx( value.A()[4] ) );
  CHECK( 4.423802e-3 == Approx( value.alphas()[0] ) );
  CHECK( 4.649528e-3 == Approx( value.alphas()[1] ) );
  CHECK( 4.886772e-3 == Approx( value.alphas()[2] ) );
  CHECK( 8.418068e+1 == Approx( value.alphas()[3] ) );
  CHECK( 8.847604e+1 == Approx( value.alphas()[4] ) );

  CHECK( 0 == value.LI().size() );
  CHECK( 0 == value.temperatureInterpolants().size() );

  values = value.S();
  CHECK( 1 == values.size() );
  CHECK( 5 == values[0].size() );
  CHECK( 2.386694e-4 == Approx( values[0][0] ) );
  CHECK( 2.508273e-4 == Approx( values[0][1] ) );
  CHECK( 2.636238e-4 == Approx( values[0][2] ) );
  CHECK( 2.770291e-4 == Approx( values[0][3] ) );
  CHECK( 2.911373e-4 == Approx( values[0][4] ) );

  values = value.thermalScatteringValues();
  CHECK( 1 == values.size() );
  CHECK( 5 == values[0].size() );
  CHECK( 2.386694e-4 == Approx( values[0][0] ) );
  CHECK( 2.508273e-4 == Approx( values[0][1] ) );
  CHECK( 2.636238e-4 == Approx( values[0][2] ) );
  CHECK( 2.770291e-4 == Approx( values[0][3] ) );
  CHECK( 2.911373e-4 == Approx( values[0][4] ) );

  CHECK( 10 == chunk.NC() );
}

std::string invalidLT() {
  return
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n";
}
