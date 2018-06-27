#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ScatteringLaw = section::Type< 7, 4 >::ScatteringLaw;
using ScatteringLawConstants = section::Type< 7, 4 >::ScatteringLawConstants;
using AnalyticalFunctions = section::Type< 7, 4 >::AnalyticalFunctions;
using Tabulated = section::Type< 7, 4 >::Tabulated;
using BetaValue = section::Type< 7, 4 >::Tabulated::BetaValue;
using EffectiveTemperature = section::Type< 7, 4 >::EffectiveTemperature;

std::string chunkWithOneTemperatureAndOneScatterer();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 7, 4 >" ) {

  GIVEN( "valid data for a section::Type< 7, 4 > with one temperature and "
         "no secondary scatterers" ) {

    double za = 127.;
    double awr = 8.934780e+0;
    int lasym = 0;
    int lat = 1;
    ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0, 6.153875e+0,
                                      8.934780e+0, 1 );
    ScatteringLaw law(
        Tabulated( { 2 }, { 4 },
                   { BetaValue( 293.6, 0.0, { 5 }, { 4 },
                                { 4.423802e-3, 4.649528e-3, 4.886772e-3, 
                                  8.418068e+1, 8.847604e+1 },
                                { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                    1.306574e-9, 5.29573e-10 } ),
                     BetaValue( 293.6, 3.952570e-2, { 5 }, { 2 },
                                { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                  8.418068e+1, 8.847604e+1 },
                                { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                  2.770291e-4, 2.911373e-4 } ) } ) );
    EffectiveTemperature principal( { 3 }, { 2 }, 
                                    { 293.6, 600., 1200. }, 
                                    { 5.332083e+2, 7.354726e+2, 1.270678e+3 } );

    THEN( "a section::Type< 7, 4 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 4 > chunk( za, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ),
                                   {} );

      REQUIRE( 127. == Approx( chunk.ZA() ) );
      REQUIRE( 8.934780e+0 == Approx( chunk.AWR() ) );
      REQUIRE( 1 == chunk.LAT() );
      REQUIRE( 0 == chunk.LASYM() );

      auto barray = chunk.constants();
      REQUIRE( 0 == barray.LLN() );
      REQUIRE( 6 == barray.NI() );
      REQUIRE( 0 == barray.NS() );

      REQUIRE( 1.976285e+2 == Approx( barray.epsilon() ) );
      REQUIRE( 5.000001e+0 == Approx( barray.upperEnergyLimit() ) );
      REQUIRE( 1 == barray.totalFreeCrossSections().size() );
      REQUIRE( 6.153875e+0 == Approx( barray.totalFreeCrossSections()[0] ) );
      REQUIRE( 1 == barray.atomicWeightRatios().size() );
      REQUIRE( 8.934780e+0 == Approx( barray.atomicWeightRatios()[0] ) );
      REQUIRE( 1 == barray.numberAtoms().size() );
      REQUIRE( 1. == Approx( barray.numberAtoms()[0] ) );
      REQUIRE( 0 == barray.analyticalFunctionTypes().size() );

      auto table = std::experimental::get< Tabulated >( chunk.scatteringLaw() );
      REQUIRE( 1 == table.NR() );
      REQUIRE( 2 == table.NB() );
      REQUIRE( 1 == table.boundaries().size() );
      REQUIRE( 2 == table.boundaries()[0] );
      REQUIRE( 1 == table.interpolants().size() );
      REQUIRE( 4 == table.interpolants()[0] );

      auto value = table.betas()[0];
      REQUIRE( 0.0 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 4 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386876e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508466e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 1.306574e-9 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 5.29573e-10 == Approx( value.thermalScatteringValues()[0][4] ) );

      value = table.betas()[1];
      REQUIRE( 3.952570e-2 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 2 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386694e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508273e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 2.770291e-4 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 2.911373e-4 == Approx( value.thermalScatteringValues()[0][4] ) );

      auto temp = chunk.principalEffectiveTemperature();
      REQUIRE( 3 == temp.NT() );
      REQUIRE( 1 == temp.NR() );
      REQUIRE( 1 == temp.interpolants().size() );
      REQUIRE( 1 == temp.boundaries().size() );
      REQUIRE( 2 == temp.interpolants()[0] );
      REQUIRE( 3 == temp.boundaries()[0] );
      REQUIRE( 3 == temp.moderatorTemperatures().size() );
      REQUIRE( 3 == temp.effectiveTemperatures().size() );
      REQUIRE( 293.6 == Approx( temp.moderatorTemperatures()[0] ) );
      REQUIRE( 600. == Approx( temp.moderatorTemperatures()[1] ) );
      REQUIRE( 1200. == Approx( temp.moderatorTemperatures()[2] ) );
      REQUIRE( 5.332083e+2 == Approx( temp.effectiveTemperatures()[0] ) );
      REQUIRE( 7.354726e+2 == Approx( temp.effectiveTemperatures()[1] ) );
      REQUIRE( 1.270678e+3 == Approx( temp.effectiveTemperatures()[2] ) );

      REQUIRE( 16 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid section::Type< 7, 4 > with one "
         "temperature and no secondary scatterers" ) {

    WHEN( "there is a valid SEND record" ){

      std::string sectionString = chunkWithOneTemperatureAndOneScatterer() + 
                                  validSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
    THEN( "a section::Type< 7, 4 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      REQUIRE( 127. == Approx( chunk.ZA() ) );
      REQUIRE( 8.934780e+0 == Approx( chunk.AWR() ) );
      REQUIRE( 1 == chunk.LAT() );
      REQUIRE( 0 == chunk.LASYM() );

      auto barray = chunk.constants();
      REQUIRE( 0 == barray.LLN() );
      REQUIRE( 6 == barray.NI() );
      REQUIRE( 0 == barray.NS() );

      REQUIRE( 1.976285e+2 == Approx( barray.epsilon() ) );
      REQUIRE( 5.000001e+0 == Approx( barray.upperEnergyLimit() ) );
      REQUIRE( 1 == barray.totalFreeCrossSections().size() );
      REQUIRE( 6.153875e+0 == Approx( barray.totalFreeCrossSections()[0] ) );
      REQUIRE( 1 == barray.atomicWeightRatios().size() );
      REQUIRE( 8.934780e+0 == Approx( barray.atomicWeightRatios()[0] ) );
      REQUIRE( 1 == barray.numberAtoms().size() );
      REQUIRE( 1. == Approx( barray.numberAtoms()[0] ) );
      REQUIRE( 0 == barray.analyticalFunctionTypes().size() );

      auto table = std::experimental::get< Tabulated >( chunk.scatteringLaw() );
      REQUIRE( 1 == table.NR() );
      REQUIRE( 2 == table.NB() );
      REQUIRE( 1 == table.boundaries().size() );
      REQUIRE( 2 == table.boundaries()[0] );
      REQUIRE( 1 == table.interpolants().size() );
      REQUIRE( 4 == table.interpolants()[0] );

      auto value = table.betas()[0];
      REQUIRE( 0.0 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 4 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386876e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508466e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 1.306574e-9 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 5.29573e-10 == Approx( value.thermalScatteringValues()[0][4] ) );

      value = table.betas()[1];
      REQUIRE( 3.952570e-2 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 2 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386694e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508273e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 2.770291e-4 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 2.911373e-4 == Approx( value.thermalScatteringValues()[0][4] ) );

      auto temp = chunk.principalEffectiveTemperature();
      REQUIRE( 3 == temp.NT() );
      REQUIRE( 1 == temp.NR() );
      REQUIRE( 1 == temp.interpolants().size() );
      REQUIRE( 1 == temp.boundaries().size() );
      REQUIRE( 2 == temp.interpolants()[0] );
      REQUIRE( 3 == temp.boundaries()[0] );
      REQUIRE( 3 == temp.moderatorTemperatures().size() );
      REQUIRE( 3 == temp.effectiveTemperatures().size() );
      REQUIRE( 293.6 == Approx( temp.moderatorTemperatures()[0] ) );
      REQUIRE( 600. == Approx( temp.moderatorTemperatures()[1] ) );
      REQUIRE( 1200. == Approx( temp.moderatorTemperatures()[2] ) );
      REQUIRE( 5.332083e+2 == Approx( temp.effectiveTemperatures()[0] ) );
      REQUIRE( 7.354726e+2 == Approx( temp.effectiveTemperatures()[1] ) );
      REQUIRE( 1.270678e+3 == Approx( temp.effectiveTemperatures()[2] ) );

      REQUIRE( 16 == chunk.NC() );
    } // THEN
    } //WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 4 > with two temperatures and "
         "no secondary scatterers" ) {

    double za = 127.;
    double awr = 8.934780e+0;
    int lasym = 0;
    int lat = 1;
    ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0, 6.153875e+0,
                                      8.934780e+0, 1 );
    ScatteringLaw law =
        Tabulated( { 2 }, { 4 },
                   { BetaValue( 0.0, { 5 }, { 4 },
                                { 4.423802e-3, 4.649528e-3, 4.886772e-3, 
                                  8.418068e+1, 8.847604e+1 },
                                {},
                                { 293.6 },
                                { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                    1.306574e-9, 5.29573e-10 } } ),
                     BetaValue( 3.952570e-2, { 5 }, { 2 },
                                { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                  8.418068e+1, 8.847604e+1 },
                                {},
                                { 293.6 },
                                { { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                    2.770291e-4, 2.911373e-4 } } ) } );
    EffectiveTemperature principal( { 3 }, { 2 }, 
                                    { 293.6, 600., 1200. }, 
                                    { 5.332083e+2, 7.354726e+2, 1.270678e+3 } );

    THEN( "a section::Type< 7, 4 > can be constructed and members can be "
          "tested" ) {
      section::Type< 7, 4 > chunk( za, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ),
                                   {} );

      REQUIRE( 127. == Approx( chunk.ZA() ) );
      REQUIRE( 8.934780e+0 == Approx( chunk.AWR() ) );
      REQUIRE( 1 == chunk.LAT() );
      REQUIRE( 0 == chunk.LASYM() );

      auto barray = chunk.constants();
      REQUIRE( 0 == barray.LLN() );
      REQUIRE( 6 == barray.NI() );
      REQUIRE( 0 == barray.NS() );

      REQUIRE( 1.976285e+2 == Approx( barray.epsilon() ) );
      REQUIRE( 5.000001e+0 == Approx( barray.upperEnergyLimit() ) );
      REQUIRE( 1 == barray.totalFreeCrossSections().size() );
      REQUIRE( 6.153875e+0 == Approx( barray.totalFreeCrossSections()[0] ) );
      REQUIRE( 1 == barray.atomicWeightRatios().size() );
      REQUIRE( 8.934780e+0 == Approx( barray.atomicWeightRatios()[0] ) );
      REQUIRE( 1 == barray.numberAtoms().size() );
      REQUIRE( 1. == Approx( barray.numberAtoms()[0] ) );
      REQUIRE( 0 == barray.analyticalFunctionTypes().size() );

      auto table = std::experimental::get< Tabulated >( chunk.scatteringLaw() );
      REQUIRE( 1 == table.NR() );
      REQUIRE( 2 == table.NB() );
      REQUIRE( 1 == table.boundaries().size() );
      REQUIRE( 2 == table.boundaries()[0] );
      REQUIRE( 1 == table.interpolants().size() );
      REQUIRE( 4 == table.interpolants()[0] );

      auto value = table.betas()[0];
      REQUIRE( 0.0 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 4 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386876e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508466e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 1.306574e-9 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 5.29573e-10 == Approx( value.thermalScatteringValues()[0][4] ) );

      value = table.betas()[1];
      REQUIRE( 3.952570e-2 == Approx( value.beta() ) );
      REQUIRE( 0 == value.LT() );
      REQUIRE( 1 == value.NT() );

      REQUIRE( 1 == value.NR() );
      REQUIRE( 5 == value.NA() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 5 == value.boundaries()[0] );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 2 == value.interpolants()[0] );

      REQUIRE( 1 == value.temperatures().size() );
      REQUIRE( 293.6 == Approx( value.temperatures()[0] ) );

      REQUIRE( 5 == value.alphas().size() );
      REQUIRE( 4.423802e-3 == Approx( value.alphas()[0] ) );
      REQUIRE( 4.649528e-3 == Approx( value.alphas()[1] ) );
      REQUIRE( 4.886772e-3 == Approx( value.alphas()[2] ) );
      REQUIRE( 8.418068e+1 == Approx( value.alphas()[3] ) );
      REQUIRE( 8.847604e+1 == Approx( value.alphas()[4] ) );

      REQUIRE( 0 == value.LI().size() );

      REQUIRE( 1 == value.thermalScatteringValues().size() );
      REQUIRE( 5 == value.thermalScatteringValues()[0].size() );
      REQUIRE( 2.386694e-4 == Approx( value.thermalScatteringValues()[0][0] ) );
      REQUIRE( 2.508273e-4 == Approx( value.thermalScatteringValues()[0][1] ) );
      REQUIRE( 2.636238e-4 == Approx( value.thermalScatteringValues()[0][2] ) );
      REQUIRE( 2.770291e-4 == Approx( value.thermalScatteringValues()[0][3] ) );
      REQUIRE( 2.911373e-4 == Approx( value.thermalScatteringValues()[0][4] ) );

      auto temp = chunk.principalEffectiveTemperature();
      REQUIRE( 3 == temp.NT() );
      REQUIRE( 1 == temp.NR() );
      REQUIRE( 1 == temp.interpolants().size() );
      REQUIRE( 1 == temp.boundaries().size() );
      REQUIRE( 2 == temp.interpolants()[0] );
      REQUIRE( 3 == temp.boundaries()[0] );
      REQUIRE( 3 == temp.moderatorTemperatures().size() );
      REQUIRE( 3 == temp.effectiveTemperatures().size() );
      REQUIRE( 293.6 == Approx( temp.moderatorTemperatures()[0] ) );
      REQUIRE( 600. == Approx( temp.moderatorTemperatures()[1] ) );
      REQUIRE( 1200. == Approx( temp.moderatorTemperatures()[2] ) );
      REQUIRE( 5.332083e+2 == Approx( temp.effectiveTemperatures()[0] ) );
      REQUIRE( 7.354726e+2 == Approx( temp.effectiveTemperatures()[1] ) );
      REQUIRE( 1.270678e+3 == Approx( temp.effectiveTemperatures()[2] ) );

      REQUIRE( 16 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid section::Type< 7, 4 > with one temperature and no secondary "
         " scatterers" ) {

    std::string string = chunkWithOneTemperatureAndOneScatterer() + 
                         validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
    section::Type< 7, 4 > section( head, begin, end, lineNumber, 27 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      section.print( output, 27, 7 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunkWithOneTemperatureAndOneScatterer() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}

std::string validSEND() {
  return
    "                                                                    27 7  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                    27 7  4     \n";
}

