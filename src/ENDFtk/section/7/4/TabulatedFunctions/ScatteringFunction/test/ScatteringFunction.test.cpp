#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/7/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ScatteringFunction =
section::Type< 7, 4 >::TabulatedFunctions::ScatteringFunction;

std::string chunkWithOneTemperature();
void verifyChunkWithOneTemperature( const ScatteringFunction& );
std::string chunkWithTwoTemperatures();
void verifyChunkWithTwoTemperatures( const ScatteringFunction& );
std::string chunkWithInconsistentBetas();

SCENARIO( "ScatteringFunction" ) {

  GIVEN( "valid data for a ScatteringFunction with only one temperature" ) {

    std::string string = chunkWithOneTemperature();

    WHEN( "the data is given explicitly" ) {

      // single temperature constructor
      double temperature = 293.6;
      double beta = 0.0;
      std::vector< long > interpolants = { 4 };
      std::vector< long > boundaries = { 5 };
      std::vector< double > alphas = { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                       8.418068e+1, 8.847604e+1 };
      std::vector< double > sab = { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                    1.306574e-9, 5.29573e-10 };

      // multiple temperature constructor with data for only one
      double Beta = 0.0;
      std::vector< long > Interpolants = { 4 };
      std::vector< long > Boundaries = { 5 };
      std::vector< double > Alphas = { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                       8.418068e+1, 8.847604e+1 };
      std::vector< long > Li = {};
      std::vector< double > Temperatures = { 293.6 };
      std::vector< std::vector< double > > Sab =
                                  { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 } };

      ScatteringFunction chunk( temperature, beta,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( alphas ),
                                std::move( sab ) );

      ScatteringFunction chunk2( Beta,
                                 std::move( Boundaries ),
                                 std::move( Interpolants ),
                                 std::move( Temperatures ),
                                 std::move( Li ),
                                 std::move( Alphas ),
                                 std::move( Sab ) );

      THEN( "a ScatteringFunction can be constructed using separate arrays and "
            "members can be tested" ) {

        verifyChunkWithOneTemperature( chunk );
      } // THEN

      THEN( "a ScatteringFunction can be constructed with the multiple "
            "temperature constructor using separate arrays and members can be "
            "tested" ) {

        verifyChunkWithOneTemperature( chunk2 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        CHECK( buffer == string );

        std::string buffer2;
        output = std::back_inserter( buffer2 );
        chunk2.print( output, 27, 7, 4 );

        CHECK( buffer2 == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ScatteringFunction chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a ScatteringFunction can be constructed and members can be "
            "tested" ) {

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

  GIVEN( "valid data for a ScatteringFunction with more than one "
         "temperature" ) {

    std::string string = chunkWithTwoTemperatures();

    WHEN( "the data is given explicitly" ) {

      double beta = 0.0;
      std::vector< long > boundaries = { 5 };
      std::vector< long > interpolants = { 4 };
      std::vector< long > li = { 4 };
      std::vector< double > alphas =
          { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 };
      std::vector< double > temperatures = { 293.6, 400.0 };
      std::vector< std::vector< double > > sab =
          { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
              1.306574e-9, 5.29573e-10 },
            { 4.430020e-4, 4.655671e-4, 4.892796e-4,
              4.510209e-8, 2.183942e-8 } };

      ScatteringFunction chunk( beta,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( temperatures ),
                                std::move( li ),
                                std::move( alphas ),
                                std::move( sab ) );

      THEN( "a ScatteringFunction can be constructed using separate arrays and "
            "members can be tested" ) {

        verifyChunkWithTwoTemperatures( chunk );
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

      ScatteringFunction chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a ScatteringFunction can be constructed and members can be tested" ) {

        verifyChunkWithTwoTemperatures( chunk );
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

    WHEN( "invalid data is used for the single temperature constructor" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        double temperature = 293.6;
        double beta = 0.0;
        std::vector< long > interpolants = { 4 };
        std::vector< long > wrongBoundaries = { 5, 6 }; // one too many
        std::vector< double > alphas = { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                         8.418068e+1, 8.847604e+1 };
        std::vector< double > sab = { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 };

        CHECK_THROWS( ScatteringFunction( temperature, beta,
                                            std::move( wrongBoundaries ),
                                            std::move( interpolants ),
                                            std::move( alphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        double temperature = 293.6;
        double beta = 0.0;
        std::vector< long > wrongInterpolants = { 4 , 2 }; // one too many
        std::vector< long > boundaries = { 5 };
        std::vector< double > alphas = { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                         8.418068e+1, 8.847604e+1 };
        std::vector< double > sab = { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 };

        CHECK_THROWS( ScatteringFunction( temperature, beta,
                                            std::move( boundaries ),
                                            std::move( wrongInterpolants ),
                                            std::move( alphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the alpha values" ) {

        double temperature = 293.6;
        double beta = 0.0;
        std::vector< long > interpolants = { 4 };
        std::vector< long > boundaries = { 5 };
        std::vector< double > wrongAlphas = { 4.423802e-3, 4.649528e-3, // one less
                                              4.886772e-3, 8.418068e+1 };
        std::vector< double > sab = { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 };

        CHECK_THROWS( ScatteringFunction( temperature, beta,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( wrongAlphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the S(a,b) values" ) {

        double temperature = 293.6;
        double beta = 0.0;
        std::vector< long > interpolants = { 4 };
        std::vector< long > boundaries = { 5 };
        std::vector< double > alphas = { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                         8.418068e+1, 8.847604e+1 };
        std::vector< double > wrongSab = { 2.386876e-4, 2.508466e-4,
                                           2.636238e-4, 1.306574e-9 }; // one less

        CHECK_THROWS( ScatteringFunction( temperature, beta,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( alphas ),
                                            std::move( wrongSab ) ) );
      } // THEN
    } // WHEN

    WHEN( "invalid data is used for the multiple temperature constructor" ) {

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the boundaries" ) {

        double beta = 0.0;
        std::vector< long > wrongBoundaries = { 5, 6 }; // wrong size
        std::vector< long > interpolants = { 4 };
        std::vector< long > li = { 4 };
        std::vector< double > alphas =
            { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 };
        std::vector< double > temperatures = { 293.6, 400.0 };
        std::vector< std::vector< double > > sab =
            { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                1.306574e-9, 5.29573e-10 },
              { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                4.510209e-8, 2.183942e-8 } };

        CHECK_THROWS( ScatteringFunction( beta,
                                            std::move( wrongBoundaries ),
                                            std::move( interpolants ),
                                            std::move( temperatures ),
                                            std::move( li ),
                                            std::move( alphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the interpolants" ) {

        double beta = 0.0;
        std::vector< long > boundaries = { 5 };
        std::vector< long > wrongInterpolants = { 4, 2 }; // wrong size
        std::vector< long > li = { 4 };
        std::vector< double > alphas =
            { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 };
        std::vector< double > temperatures = { 293.6, 400.0 };
        std::vector< std::vector< double > > sab =
            { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                1.306574e-9, 5.29573e-10 },
              { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                4.510209e-8, 2.183942e-8 } };

        CHECK_THROWS( ScatteringFunction( beta,
                                            std::move( boundaries ),
                                            std::move( wrongInterpolants ),
                                            std::move( temperatures ),
                                            std::move( li ),
                                            std::move( alphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the alpha values" ) {

        double beta = 0.0;
        std::vector< long > boundaries = { 5 };
        std::vector< long > interpolants = { 4 };
        std::vector< long > li = { 4 };
        std::vector< double > wrongAlphas = // wrong size: one less alpha
            { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1 };
        std::vector< double > temperatures = { 293.6, 400.0 };
        std::vector< std::vector< double > > sab =
            { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                1.306574e-9, 5.29573e-10 },
              { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                4.510209e-8, 2.183942e-8 } };

        CHECK_THROWS( ScatteringFunction( beta,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( temperatures ),
                                            std::move( li ),
                                            std::move( wrongAlphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the temperatures" ) {

        double beta = 0.0;
        std::vector< long > boundaries = { 5 };
        std::vector< long > interpolants = { 4 };
        std::vector< long > li = { 4 };
        std::vector< double > alphas =
            { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 };
        std::vector< double > wrongTemperatures = { 293.6 }; // one less value
        std::vector< std::vector< double > > sab =
            { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                1.306574e-9, 5.29573e-10 },
              { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                4.510209e-8, 2.183942e-8 } };

        CHECK_THROWS( ScatteringFunction( beta,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( wrongTemperatures ),
                                            std::move( li ),
                                            std::move( alphas ),
                                            std::move( sab ) ) );
      } // THEN

      THEN( "an exception is thrown upon construction when there is "
            "something wrong with the S(a,b) values" ) {

        double beta = 0.0;
        std::vector< long > boundaries = { 5 };
        std::vector< long > interpolants = { 4 };
        std::vector< long > li = { 4 };
        std::vector< double > alphas =
            { 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 };
        std::vector< double > temperatures = { 293.6, 400.0 };
        std::vector< std::vector< double > > wrongSab =
            { { 2.386876e-4, 2.508466e-4, // wrong size
                1.306574e-9, 5.29573e-10 },
              { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                4.510209e-8, 2.183942e-8 } };

        CHECK_THROWS( ScatteringFunction( beta,
                                            std::move( boundaries ),
                                            std::move( interpolants ),
                                            std::move( temperatures ),
                                            std::move( li ),
                                            std::move( alphas ),
                                            std::move( wrongSab ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a ScatteringFunction with two temperatures "
          "and inconsistent betas" ) {

      std::string string = chunkWithInconsistentBetas();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScatteringFunction( begin, end, lineNumber,
                                            27, 7, 4 ) );
      } //THEN
    } //WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithOneTemperature() {
  return
    " 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n";
}

void verifyChunkWithOneTemperature( const ScatteringFunction& chunk ) {

  CHECK( 0.0 == Approx( chunk.B() ) );
  CHECK( 0.0 == Approx( chunk.beta() ) );
  CHECK( 0 == chunk.LT() );
  CHECK( 0 == chunk.temperatureDependenceFlag() );
  CHECK( 1 == chunk.NT() );
  CHECK( 1 == chunk.numberTemperatures() );

  CHECK( 1 == chunk.NR() );
  CHECK( 5 == chunk.NP() );
  CHECK( 5 == chunk.NA() );
  CHECK( 5 == chunk.numberAlphas() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 5 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 4 == chunk.interpolants()[0] );

  CHECK( 1 == chunk.T().size() );
  CHECK( 1 == chunk.temperatures().size() );
  CHECK( 293.6 == Approx( chunk.T()[0] ) );
  CHECK( 293.6 == Approx( chunk.temperatures()[0] ) );

  CHECK( 5 == chunk.A().size() );
  CHECK( 5 == chunk.alphas().size() );
  CHECK( 4.423802e-3 == Approx( chunk.A()[0] ) );
  CHECK( 4.649528e-3 == Approx( chunk.A()[1] ) );
  CHECK( 4.886772e-3 == Approx( chunk.A()[2] ) );
  CHECK( 8.418068e+1 == Approx( chunk.A()[3] ) );
  CHECK( 8.847604e+1 == Approx( chunk.A()[4] ) );
  CHECK( 4.423802e-3 == Approx( chunk.alphas()[0] ) );
  CHECK( 4.649528e-3 == Approx( chunk.alphas()[1] ) );
  CHECK( 4.886772e-3 == Approx( chunk.alphas()[2] ) );
  CHECK( 8.418068e+1 == Approx( chunk.alphas()[3] ) );
  CHECK( 8.847604e+1 == Approx( chunk.alphas()[4] ) );

  CHECK( 0 == chunk.LI().size() );
  CHECK( 0 == chunk.temperatureInterpolants().size() );

  CHECK( 1 == chunk.S().size() );
  CHECK( 5 == chunk.S()[0].size() );
  CHECK( 2.386876e-4 == Approx( chunk.S()[0][0] ) );
  CHECK( 2.508466e-4 == Approx( chunk.S()[0][1] ) );
  CHECK( 2.636238e-4 == Approx( chunk.S()[0][2] ) );
  CHECK( 1.306574e-9 == Approx( chunk.S()[0][3] ) );
  CHECK( 5.29573e-10 == Approx( chunk.S()[0][4] ) );

  CHECK( 1 == chunk.thermalScatteringValues().size() );
  CHECK( 5 == chunk.thermalScatteringValues()[0].size() );
  CHECK( 2.386876e-4 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  CHECK( 2.508466e-4 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  CHECK( 2.636238e-4 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  CHECK( 1.306574e-9 == Approx( chunk.thermalScatteringValues()[0][3] ) );
  CHECK( 5.29573e-10 == Approx( chunk.thermalScatteringValues()[0][4] ) );

  CHECK( 4 == chunk.NC() );
}
std::string chunkWithTwoTemperatures() {
  return
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 4.000000+2 0.000000+0          4          0          5          0  27 7  4     \n"
    " 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n";
}

void verifyChunkWithTwoTemperatures( const ScatteringFunction& chunk ) {

  CHECK( 0.0 == Approx( chunk.B() ) );
  CHECK( 0.0 == Approx( chunk.beta() ) );
  CHECK( 1 == chunk.LT() );
  CHECK( 1 == chunk.temperatureDependenceFlag() );
  CHECK( 2 == chunk.NT() );
  CHECK( 2 == chunk.numberTemperatures() );

  CHECK( 1 == chunk.NR() );
  CHECK( 5 == chunk.NP() );
  CHECK( 5 == chunk.NA() );
  CHECK( 5 == chunk.numberAlphas() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 5 == chunk.boundaries()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 4 == chunk.interpolants()[0] );

  CHECK( 2 == chunk.T().size() );
  CHECK( 2 == chunk.temperatures().size() );
  CHECK( 293.6 == Approx( chunk.T()[0] ) );
  CHECK( 400.0 == Approx( chunk.T()[1] ) );
  CHECK( 293.6 == Approx( chunk.temperatures()[0] ) );
  CHECK( 400.0 == Approx( chunk.temperatures()[1] ) );

  CHECK( 5 == chunk.A().size() );
  CHECK( 5 == chunk.alphas().size() );
  CHECK( 4.423802e-3 == Approx( chunk.A()[0] ) );
  CHECK( 4.649528e-3 == Approx( chunk.A()[1] ) );
  CHECK( 4.886772e-3 == Approx( chunk.A()[2] ) );
  CHECK( 8.418068e+1 == Approx( chunk.A()[3] ) );
  CHECK( 8.847604e+1 == Approx( chunk.A()[4] ) );
  CHECK( 4.423802e-3 == Approx( chunk.alphas()[0] ) );
  CHECK( 4.649528e-3 == Approx( chunk.alphas()[1] ) );
  CHECK( 4.886772e-3 == Approx( chunk.alphas()[2] ) );
  CHECK( 8.418068e+1 == Approx( chunk.alphas()[3] ) );
  CHECK( 8.847604e+1 == Approx( chunk.alphas()[4] ) );

  CHECK( 1 == chunk.LI().size() );
  CHECK( 4 == chunk.LI()[0] );
  CHECK( 1 == chunk.temperatureInterpolants().size() );
  CHECK( 4 == chunk.temperatureInterpolants()[0] );

  CHECK( 2 == chunk.S().size() );
  CHECK( 5 == chunk.S()[0].size() );
  CHECK( 2.386876e-4 == Approx( chunk.S()[0][0] ) );
  CHECK( 2.508466e-4 == Approx( chunk.S()[0][1] ) );
  CHECK( 2.636238e-4 == Approx( chunk.S()[0][2] ) );
  CHECK( 1.306574e-9 == Approx( chunk.S()[0][3] ) );
  CHECK( 5.29573e-10 == Approx( chunk.S()[0][4] ) );
  CHECK( 5 == chunk.S()[1].size() );
  CHECK( 4.430020e-4 == Approx( chunk.S()[1][0] ) );
  CHECK( 4.655671e-4 == Approx( chunk.S()[1][1] ) );
  CHECK( 4.892796e-4 == Approx( chunk.S()[1][2] ) );
  CHECK( 4.510209e-8 == Approx( chunk.S()[1][3] ) );
  CHECK( 2.183942e-8 == Approx( chunk.S()[1][4] ) );

  CHECK( 2 == chunk.thermalScatteringValues().size() );
  CHECK( 5 == chunk.thermalScatteringValues()[0].size() );
  CHECK( 2.386876e-4 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  CHECK( 2.508466e-4 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  CHECK( 2.636238e-4 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  CHECK( 1.306574e-9 == Approx( chunk.thermalScatteringValues()[0][3] ) );
  CHECK( 5.29573e-10 == Approx( chunk.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == chunk.thermalScatteringValues()[1].size() );
  CHECK( 4.430020e-4 == Approx( chunk.thermalScatteringValues()[1][0] ) );
  CHECK( 4.655671e-4 == Approx( chunk.thermalScatteringValues()[1][1] ) );
  CHECK( 4.892796e-4 == Approx( chunk.thermalScatteringValues()[1][2] ) );
  CHECK( 4.510209e-8 == Approx( chunk.thermalScatteringValues()[1][3] ) );
  CHECK( 2.183942e-8 == Approx( chunk.thermalScatteringValues()[1][4] ) );

  CHECK( 6 == chunk.NC() );
}
std::string chunkWithInconsistentBetas() {
  return
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 4.000000+2 1.000000+0          4          0          5          0  27 7  4     \n"
    " 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n";
}
