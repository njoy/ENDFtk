#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using BetaValue = 
section::Type< 7, 4 >::Tabulated::BetaValue;

std::string chunkWithOneTemperature();
void verifyChunkWithOneTemperature( const BetaValue& );
std::string chunkWithTwoTemperatures();
void verifyChunkWithTwoTemperatures( const BetaValue& );
std::string chunkWithInconsistentBetas();

SCENARIO( "BetaValue" ) {

  GIVEN( "valid data for a BetaValue with only one temperature" ) {

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

      BetaValue chunk( temperature, beta,
                       std::move( boundaries ),
                       std::move( interpolants ), 
                       std::move( alphas ),
                       std::move( sab ) );

      BetaValue chunk2( Beta,
                        std::move( Boundaries ),
                        std::move( Interpolants ), 
                        std::move( Temperatures ),
                        std::move( Li ),
                        std::move( Alphas ),
                        std::move( Sab ) );

      THEN( "a BetaValue can be constructed using separate arrays and members "
            "can be tested" ) {

        verifyChunkWithOneTemperature( chunk );
      } // THEN

      THEN( "a BetaValue can be constructed with the multiple temperature "
            "constructor using separate arrays and members can be tested" ) {

        verifyChunkWithOneTemperature( chunk2 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );

        std::string buffer2;
        output = std::back_inserter( buffer2 );
        chunk2.print( output, 27, 7, 4 );

        REQUIRE( buffer2 == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      BetaValue chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a BetaValue can be constructed and members can be tested" ) {

        verifyChunkWithOneTemperature( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a BetaValue with more than one temperature" ) {

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

      BetaValue chunk( beta,
                       std::move( boundaries ),
                       std::move( interpolants ), 
                       std::move( temperatures ),
                       std::move( li ),
                       std::move( alphas ),
                       std::move( sab ) );

      THEN( "a BetaValue can be constructed using separate arrays and members "
            "can be tested" ) {

        verifyChunkWithTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      BetaValue chunk( begin, end, lineNumber, 27, 7, 4 );

      THEN( "a BetaValue can be constructed and members can be tested" ) {

        verifyChunkWithTwoTemperatures( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7, 4 );

        REQUIRE( buffer == string );
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

        REQUIRE_THROWS( BetaValue( temperature, beta,
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

        REQUIRE_THROWS( BetaValue( temperature, beta,
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

        REQUIRE_THROWS( BetaValue( temperature, beta,
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

        REQUIRE_THROWS( BetaValue( temperature, beta,
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

        REQUIRE_THROWS( BetaValue( beta,
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

        REQUIRE_THROWS( BetaValue( beta,
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

        REQUIRE_THROWS( BetaValue( beta,
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

        REQUIRE_THROWS( BetaValue( beta,
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

        REQUIRE_THROWS( BetaValue( beta,
                                   std::move( boundaries ),
                                   std::move( interpolants ), 
                                   std::move( temperatures ),
                                   std::move( li ),
                                   std::move( alphas ),
                                   std::move( wrongSab ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a BetaValue with two temperatures "
          "and inconsistent betas" ) {

      std::string string = chunkWithInconsistentBetas();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( BetaValue( begin, end, lineNumber, 27, 7, 4 ) );
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

void verifyChunkWithOneTemperature( const BetaValue& chunk ) {

  REQUIRE( 0.0 == Approx( chunk.beta() ) );
  REQUIRE( 0 == chunk.LT() );
  REQUIRE( 0 == chunk.temperatureDependenceFlag() );
  REQUIRE( 1 == chunk.NT() );
  REQUIRE( 1 == chunk.numberTemperatures() );

  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 5 == chunk.NA() );
  REQUIRE( 5 == chunk.numberAlphas() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 5 == chunk.boundaries()[0] );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 4 == chunk.interpolants()[0] );

  REQUIRE( 1 == chunk.temperatures().size() );
  REQUIRE( 293.6 == Approx( chunk.temperatures()[0] ) );

  REQUIRE( 5 == chunk.alphas().size() );
  REQUIRE( 4.423802e-3 == Approx( chunk.alphas()[0] ) );
  REQUIRE( 4.649528e-3 == Approx( chunk.alphas()[1] ) );
  REQUIRE( 4.886772e-3 == Approx( chunk.alphas()[2] ) );
  REQUIRE( 8.418068e+1 == Approx( chunk.alphas()[3] ) );
  REQUIRE( 8.847604e+1 == Approx( chunk.alphas()[4] ) );

  REQUIRE( 0 == chunk.LI().size() );
  REQUIRE( 0 == chunk.temperatureInterpolants().size() );

  REQUIRE( 1 == chunk.thermalScatteringValues().size() );
  REQUIRE( 5 == chunk.thermalScatteringValues()[0].size() );
  REQUIRE( 2.386876e-4 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  REQUIRE( 2.508466e-4 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  REQUIRE( 2.636238e-4 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  REQUIRE( 1.306574e-9 == Approx( chunk.thermalScatteringValues()[0][3] ) );
  REQUIRE( 5.29573e-10 == Approx( chunk.thermalScatteringValues()[0][4] ) );

  REQUIRE( 4 == chunk.NC() );
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

void verifyChunkWithTwoTemperatures( const BetaValue& chunk ) {

  REQUIRE( 0.0 == Approx( chunk.beta() ) );
  REQUIRE( 1 == chunk.LT() );
  REQUIRE( 1 == chunk.temperatureDependenceFlag() );
  REQUIRE( 2 == chunk.NT() );
  REQUIRE( 2 == chunk.numberTemperatures() );

  REQUIRE( 1 == chunk.NR() );
  REQUIRE( 5 == chunk.NA() );
  REQUIRE( 5 == chunk.numberAlphas() );
  REQUIRE( 1 == chunk.boundaries().size() );
  REQUIRE( 5 == chunk.boundaries()[0] );
  REQUIRE( 1 == chunk.interpolants().size() );
  REQUIRE( 4 == chunk.interpolants()[0] );

  REQUIRE( 2 == chunk.temperatures().size() );
  REQUIRE( 293.6 == Approx( chunk.temperatures()[0] ) );
  REQUIRE( 400.0 == Approx( chunk.temperatures()[1] ) );

  REQUIRE( 5 == chunk.alphas().size() );
  REQUIRE( 4.423802e-3 == Approx( chunk.alphas()[0] ) );
  REQUIRE( 4.649528e-3 == Approx( chunk.alphas()[1] ) );
  REQUIRE( 4.886772e-3 == Approx( chunk.alphas()[2] ) );
  REQUIRE( 8.418068e+1 == Approx( chunk.alphas()[3] ) );
  REQUIRE( 8.847604e+1 == Approx( chunk.alphas()[4] ) );

  REQUIRE( 1 == chunk.LI().size() );
  REQUIRE( 4 == chunk.LI()[0] );
  REQUIRE( 1 == chunk.temperatureInterpolants().size() );
  REQUIRE( 4 == chunk.temperatureInterpolants()[0] );

  REQUIRE( 2 == chunk.thermalScatteringValues().size() );
  REQUIRE( 5 == chunk.thermalScatteringValues()[0].size() );
  REQUIRE( 2.386876e-4 == Approx( chunk.thermalScatteringValues()[0][0] ) );
  REQUIRE( 2.508466e-4 == Approx( chunk.thermalScatteringValues()[0][1] ) );
  REQUIRE( 2.636238e-4 == Approx( chunk.thermalScatteringValues()[0][2] ) );
  REQUIRE( 1.306574e-9 == Approx( chunk.thermalScatteringValues()[0][3] ) );
  REQUIRE( 5.29573e-10 == Approx( chunk.thermalScatteringValues()[0][4] ) );
  REQUIRE( 5 == chunk.thermalScatteringValues()[1].size() );
  REQUIRE( 4.430020e-4 == Approx( chunk.thermalScatteringValues()[1][0] ) );
  REQUIRE( 4.655671e-4 == Approx( chunk.thermalScatteringValues()[1][1] ) );
  REQUIRE( 4.892796e-4 == Approx( chunk.thermalScatteringValues()[1][2] ) );
  REQUIRE( 4.510209e-8 == Approx( chunk.thermalScatteringValues()[1][3] ) );
  REQUIRE( 2.183942e-8 == Approx( chunk.thermalScatteringValues()[1][4] ) );

  REQUIRE( 6 == chunk.NC() );
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

