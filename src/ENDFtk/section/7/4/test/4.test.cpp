// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/7/4.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ScatteringLaw = section::Type< 7, 4 >::ScatteringLaw;
using ScatteringLawConstants = section::Type< 7, 4 >::ScatteringLawConstants;
using AnalyticalFunctions = section::Type< 7, 4 >::AnalyticalFunctions;
using TabulatedFunctions = section::Type< 7, 4 >::TabulatedFunctions;
using ScatteringFunction = section::Type< 7, 4 >::TabulatedFunctions::ScatteringFunction;
using EffectiveTemperature = section::Type< 7, 4 >::EffectiveTemperature;

// macros don't like multiple template arguments
using section74 = section::Type< 7, 4 >;

std::string chunkWithAnalyticalFunctions();
void verifyChunkWithAnalyticalFunctions(
       const section::Type< 7, 4 >& );
std::string chunkWithOneTemperatureAndOneScatterer();
void verifyChunkWithOneTemperatureAndOneScatterer(
       const section::Type< 7, 4 >& );
std::string chunkWithTwoTemperaturesAndOneScatterer();
void verifyChunkWithTwoTemperaturesAndOneScatterer(
       const section::Type< 7, 4 >& );
std::string chunkWithTwoTemperaturesAndTwoScatterers();
void verifyChunkWithTwoTemperaturesAndTwoScatterers(
       const section::Type< 7, 4 >& );
std::string chunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature();
void verifyChunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature(
       const section::Type< 7, 4 >& );
std::string chunkWithInvalidLAT();
std::string chunkWithInvalidLASYM();
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 7, 4 >" ) {

  GIVEN( "valid data for a section::Type< 7, 4 > with only analytical "
         "functions (i.e. B(1)=0)" ) {

    std::string sectionString = chunkWithAnalyticalFunctions() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0,
                                        0, 8.934780e+0, 1 );
      ScatteringLaw law = AnalyticalFunctions();
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );

      section::Type< 7, 4 > chunk( zaid, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ) );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithAnalyticalFunctions( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
          "tested" ) {

        verifyChunkWithAnalyticalFunctions( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 4, std::string( sectionString ) );

      section::Type< 7, 4 > chunk = section.parse< 7, 4 >();

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithAnalyticalFunctions( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 4 > with one temperature and "
         "no secondary scatterers" ) {

    std::string sectionString = chunkWithOneTemperatureAndOneScatterer() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0,
                                        6.153875e+0, 8.934780e+0, 1 );
      ScatteringLaw law(
          TabulatedFunctions( { 2 }, { 4 },
                     { ScatteringFunction(
                                  293.6, 0.0, { 5 }, { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 } ),
                       ScatteringFunction(
                                  293.6, 3.952570e-2, { 5 }, { 2 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                    2.770291e-4, 2.911373e-4 } ) } ) );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );

      section::Type< 7, 4 > chunk( zaid, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ) );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneTemperatureAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
          "tested" ) {

        verifyChunkWithOneTemperatureAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 4, std::string( sectionString ) );

      section::Type< 7, 4 > chunk = section.parse< 7, 4 >();

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOneTemperatureAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 4 > with two temperatures and "
         "no secondary scatterers" ) {

    std::string sectionString = chunkWithTwoTemperaturesAndOneScatterer() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0,
                                        6.153875e+0, 8.934780e+0, 1 );
      ScatteringLaw law =
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction(
                                  0.0, { 5 }, { 4 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 },
                                    { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                                      4.510209e-8, 2.183942e-8 } } ),
                       ScatteringFunction(
                                  3.952570e-2, { 5 }, { 2 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                      2.770291e-4, 2.911373e-4 },
                                    { 6.921141e-4, 7.273641e-4, 7.644060e-4,
                                      8.033305e-4, 8.442328e-4 } } ) } );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );

      section::Type< 7, 4 > chunk( zaid, awr, lat, lasym,
                                  std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ) );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 4, std::string( sectionString ) );

      section::Type< 7, 4 > chunk = section.parse< 7, 4 >();

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndOneScatterer( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 4 > with two temperatures and "
         "one secondary scatterer with a secondary temperature" ) {

    std::string sectionString = chunkWithTwoTemperaturesAndTwoScatterers() +
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1, 1.976285e+2, 5.000001e+0,
                                        { 6.153875e+0, 3.748750e+0 },
                                        { 8.934780e+0, 1.586200e+1 },
                                        { 1, 2 }, { 0 } );

      ScatteringLaw law =
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction(
                                  0.0, { 5 }, { 4 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 },
                                    { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                                      4.510209e-8, 2.183942e-8 } } ),
                       ScatteringFunction(
                                  3.952570e-2, { 5 }, { 2 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                      2.770291e-4, 2.911373e-4 },
                                    { 6.921141e-4, 7.273641e-4, 7.644060e-4,
                                      8.033305e-4, 8.442328e-4 } } ) } );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );
      EffectiveTemperature secondary( { 2 }, { 2 },
                                      { 293.6, 1200. },
                                      { 300.0, 1250. } );

      section::Type< 7, 4 >
      chunk( zaid, awr, lat, lasym,
             std::move( constants ),
             std::move( law ),
             std::move( principal ),
             { std::optional< EffectiveTemperature >( secondary ) } );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndTwoScatterers( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndTwoScatterers( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 4, std::string( sectionString ) );

      section::Type< 7, 4 > chunk = section.parse< 7, 4 >();

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesAndTwoScatterers( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 7, 4 > with two temperatures and "
         "one secondary scatterer without a secondary temperature" ) {

    std::string sectionString =
            chunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature() +
            validSEND();

    WHEN( "the data is given explicitly" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1, 1.976285e+2, 5.000001e+0,
                                        { 6.153875e+0, 3.748750e+0 },
                                        { 8.934780e+0, 1.586200e+1 },
                                        { 1, 2 }, { 1 } );

      ScatteringLaw law =
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction(
                                  0.0, { 5 }, { 4 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 },
                                    { 4.430020e-4, 4.655671e-4, 4.892796e-4,
                                      4.510209e-8, 2.183942e-8 } } ),
                       ScatteringFunction(
                                  3.952570e-2, { 5 }, { 2 },
                                  { 293.6, 400 },
                                  { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                      2.770291e-4, 2.911373e-4 },
                                    { 6.921141e-4, 7.273641e-4, 7.644060e-4,
                                      8.033305e-4, 8.442328e-4 } } ) } );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );
      std::vector< std::optional< EffectiveTemperature > > secondary =
              { std::nullopt };

      section::Type< 7, 4 >
      chunk( zaid, awr, lat, lasym,
             std::move( constants ),
             std::move( law ),
             std::move( principal ),
             secondary );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature(
               chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 7, 4 > chunk( head, begin, end, lineNumber, 27 );

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature(
               chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 27, 7, 4, std::string( sectionString ) );

      section::Type< 7, 4 > chunk = section.parse< 7, 4 >();

      THEN( "a section::Type< 7, 4 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature(
               chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 27, 7 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 7, 4 >" ) {

    WHEN( "invalid LAT values are given" ) {

      std::vector< int > invalid = { -1, 2, 5, 10 };

      THEN( "an exception is thrown" ){

        for ( auto lat : invalid ) {

          int zaid = 127;
          double awr = 8.934780e+0;
          int lasym = 0;
          ScatteringLawConstants constants( 0, 1.976285e+2, 5.000001e+0,
                                            6.153875e+0, 8.934780e+0, 1 );
          ScatteringLaw law(
              TabulatedFunctions(
                         { 2 }, { 4 },
                         { ScatteringFunction(
                                      293.6, 0.0, { 5 }, { 4 },
                                      { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                        8.418068e+1, 8.847604e+1 },
                                      { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                          1.306574e-9, 5.29573e-10 } ),
                           ScatteringFunction(
                                      293.6, 3.952570e-2, { 5 }, { 2 },
                                      { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                        8.418068e+1, 8.847604e+1 },
                                      { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                        2.770291e-4, 2.911373e-4 } ) } ) );
          EffectiveTemperature principal( { 3 }, { 2 },
                                          { 293.6, 600., 1200. },
                                          { 5.332083e+2, 7.354726e+2,
                                            1.270678e+3 } );

          CHECK_THROWS( section74( zaid, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ) ) );
        } // THEN
      } // THEN
    } // WHEN

    WHEN( "no effective temperature is given for a secondary scatterer "
          "with B(7) == 0.0" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1, 1.976285e+2, 5.000001e+0,
                                        { 6.153875e+0, 4.0 },
                                        { 8.934780e+0, 2.0 },
                                        { 1, 1 }, { 0 } );

      ScatteringLaw law(
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction(
                                  293.6, 0.0, { 5 }, { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 } ),
                       ScatteringFunction(
                                  293.6, 3.952570e-2, { 5 }, { 2 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                    2.770291e-4, 2.911373e-4 } ) } ) );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );

      THEN( "an exception is thrown" ) {

          CHECK_THROWS( section74( zaid, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ) ) );
      }
    }

    WHEN( "an effective temperature equal to std::nullopt is given for a "
          "secondary scatterer with B(7) == 0.0" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1, 1.976285e+2, 5.000001e+0,
                                        { 6.153875e+0, 4.0 },
                                        { 8.934780e+0, 2.0 },
                                        { 1, 1 }, { 0 } );

      ScatteringLaw law(
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction( 293.6, 0.0, { 5 }, { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 } ),
                       ScatteringFunction( 293.6, 3.952570e-2, { 5 }, { 2 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                    2.770291e-4, 2.911373e-4 } ) } ) );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );
      EffectiveTemperature secondary( { 2 }, { 2 },
                                      { 293.6, 1200. },
                                      { 300.0, 1250. } );

      THEN( "an exception is thrown" ) {

          CHECK_THROWS( section74( zaid, awr, lat, lasym,
                                   std::move( constants ),
                                   std::move( law ),
                                   std::move( principal ),
                                   { std::nullopt } ) );
      }
    }

    WHEN( "an effective temperature is given for a secondary scatterer "
          "with B(7) != 0.0" ) {

      int zaid = 127;
      double awr = 8.934780e+0;
      int lasym = 0;
      int lat = 1;
      ScatteringLawConstants constants( 0, 1, 1.976285e+2, 5.000001e+0,
                                        { 6.153875e+0, 4.0 },
                                        { 8.934780e+0, 2.0 },
                                        { 1, 1 }, { 1 } );

      ScatteringLaw law(
          TabulatedFunctions(
                     { 2 }, { 4 },
                     { ScatteringFunction( 293.6, 0.0, { 5 }, { 4 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                      1.306574e-9, 5.29573e-10 } ),
                       ScatteringFunction( 293.6, 3.952570e-2, { 5 }, { 2 },
                                  { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                    8.418068e+1, 8.847604e+1 },
                                  { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                    2.770291e-4, 2.911373e-4 } ) } ) );
      EffectiveTemperature principal( { 3 }, { 2 },
                                      { 293.6, 600., 1200. },
                                      { 5.332083e+2, 7.354726e+2,
                                        1.270678e+3 } );
      EffectiveTemperature secondary( { 2 }, { 2 },
                                      { 293.6, 1200. },
                                      { 300.0, 1250. } );

      THEN( "an exception is thrown" ) {

          CHECK_THROWS(
              section74( zaid, awr, lat, lasym,
                         std::move( constants ),
                         std::move( law ),
                         std::move( principal ),
                         { std::optional< EffectiveTemperature >(
                               secondary ) } ) );
      }
    }

    WHEN( "a string representation of a valid section::Type< 7, 4 > is "
          "used with an invalid LAT" ) {

      std::string sectionString = chunkWithInvalidLAT() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section74( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 7, 4 > is "
          "used with an invalid LASYM" ) {

      std::string sectionString = chunkWithInvalidLASYM() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section74( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 7, 4 > with one "
          "temperature and no secondary scatterers with an invalid SEND" ) {

      std::string sectionString = chunkWithOneTemperatureAndOneScatterer() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section74( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 7, 4 > with two "
          "temperatures and one secondary scatterers with an invalid SEND" ) {

      std::string sectionString = chunkWithTwoTemperaturesAndOneScatterer() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section74( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 7, 4 > with two "
          "temperatures and one secondary scatterer without a secondary "
          "temperature with an invalid SEND" ) {

      std::string sectionString =
              chunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature() +
              invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section74( head, begin, end, lineNumber, 27 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithAnalyticalFunctions() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 0.000000+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}

void verifyChunkWithAnalyticalFunctions(
       const section::Type< 7, 4 >& chunk ) {

  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.sectionNumber() );

  CHECK( 127 == chunk.ZA() );
  CHECK( 127 == chunk.targetIdentifier() );
  CHECK_THAT( 8.934780e+0, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LAT() );
  CHECK( 1 == chunk.temperatureOption() );
  CHECK( 0 == chunk.LASYM() );
  CHECK( 0 == chunk.symmetryOption() );

  auto barray = chunk.constants();
  CHECK( 0 == barray.LLN() );
  CHECK( 0 == barray.sabStorageType() );
  CHECK( 6 == barray.NI() );
  CHECK( 6 == barray.numberConstants() );
  CHECK( 0 == barray.NS() );
  CHECK( 0 == barray.numberNonPrincipalScatterers() );

  CHECK_THAT( 1.976285e+2, WithinRel( barray.epsilon() ) );
  CHECK_THAT( 5.000001e+0, WithinRel( barray.upperEnergyLimit() ) );
  CHECK( 1 == barray.totalFreeCrossSections().size() );
  CHECK_THAT( 0.000000+0, WithinRel( barray.totalFreeCrossSections()[0] ) );
  CHECK( 1 == barray.atomicWeightRatios().size() );
  CHECK_THAT( 8.934780e+0, WithinRel( barray.atomicWeightRatios()[0] ) );
  CHECK( 1 == barray.numberAtoms().size() );
  CHECK_THAT( 1., WithinRel( barray.numberAtoms()[0] ) );
  CHECK( 0 == barray.analyticalFunctionTypes().size() );

  auto table = std::get< AnalyticalFunctions >( chunk.scatteringLaw() );
  CHECK( 0 == table.NC() );

  auto temp = chunk.principalEffectiveTemperature();
  CHECK( 3 == temp.NT() );
  CHECK( 3 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 3 == temp.boundaries()[0] );
  CHECK( 3 == temp.moderatorTemperatures().size() );
  CHECK( 3 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( temp.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( temp.effectiveTemperatures()[2] ) );

  // no secondary scatterer => 0 secondary temperature
  CHECK( 0 == chunk.secondaryEffectiveTemperatures().size() );

  CHECK( 6 == chunk.NC() );
}

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

void verifyChunkWithOneTemperatureAndOneScatterer(
       const section::Type< 7, 4 >& chunk ) {

  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.sectionNumber() );

  CHECK( 127 == chunk.ZA() );
  CHECK( 127 == chunk.targetIdentifier() );
  CHECK_THAT( 8.934780e+0, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LAT() );
  CHECK( 1 == chunk.temperatureOption() );
  CHECK( 0 == chunk.LASYM() );
  CHECK( 0 == chunk.symmetryOption() );

  auto barray = chunk.constants();
  CHECK( 0 == barray.LLN() );
  CHECK( 0 == barray.sabStorageType() );
  CHECK( 6 == barray.NI() );
  CHECK( 6 == barray.numberConstants() );
  CHECK( 0 == barray.NS() );
  CHECK( 0 == barray.numberNonPrincipalScatterers() );

  CHECK_THAT( 1.976285e+2, WithinRel( barray.epsilon() ) );
  CHECK_THAT( 5.000001e+0, WithinRel( barray.upperEnergyLimit() ) );
  CHECK( 1 == barray.totalFreeCrossSections().size() );
  CHECK_THAT( 6.153875e+0, WithinRel( barray.totalFreeCrossSections()[0] ) );
  CHECK( 1 == barray.atomicWeightRatios().size() );
  CHECK_THAT( 8.934780e+0, WithinRel( barray.atomicWeightRatios()[0] ) );
  CHECK( 1 == barray.numberAtoms().size() );
  CHECK_THAT( 1., WithinRel( barray.numberAtoms()[0] ) );
  CHECK( 0 == barray.analyticalFunctionTypes().size() );

  auto table = std::get< TabulatedFunctions >( chunk.scatteringLaw() );
  CHECK( 1 == table.NR() );
  CHECK( 2 == table.NB() );
  CHECK( 2 == table.numberBetas() );
  CHECK( 1 == table.boundaries().size() );
  CHECK( 2 == table.boundaries()[0] );
  CHECK( 1 == table.interpolants().size() );
  CHECK( 4 == table.interpolants()[0] );

  CHECK( 2 == table.B().size() );
  CHECK( 2 == table.betas().size() );
  CHECK_THAT( 0.0, WithinRel( table.B()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.B()[1] ) );
  CHECK_THAT( 0.0, WithinRel( table.betas()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.betas()[1] ) );

  auto value = table.scatteringFunctions()[0];
  CHECK_THAT( 0.0, WithinRel( value.beta() ) );
  CHECK( 0 == value.LT() );
  CHECK( 0 == value.temperatureDependenceFlag() );
  CHECK( 1 == value.NT() );
  CHECK( 1 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 4 == value.interpolants()[0] );

  CHECK( 1 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 0 == value.LI().size() );
  CHECK( 0 == value.temperatureInterpolants().size() );

  CHECK( 1 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386876e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508466e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 1.306574e-9, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 5.29573e-10, WithinRel( value.thermalScatteringValues()[0][4] ) );

  value = table.scatteringFunctions()[1];
  CHECK_THAT( 3.952570e-2, WithinRel( value.beta() ) );
  CHECK( 0 == value.LT() );
  CHECK( 0 == value.temperatureDependenceFlag() );
  CHECK( 1 == value.NT() );
  CHECK( 1 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 2 == value.interpolants()[0] );

  CHECK( 1 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 0 == value.LI().size() );
  CHECK( 0 == value.temperatureInterpolants().size() );

  CHECK( 1 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386694e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508273e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 2.770291e-4, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 2.911373e-4, WithinRel( value.thermalScatteringValues()[0][4] ) );

  auto temp = chunk.principalEffectiveTemperature();
  CHECK( 3 == temp.NT() );
  CHECK( 3 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 3 == temp.boundaries()[0] );
  CHECK( 3 == temp.moderatorTemperatures().size() );
  CHECK( 3 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( temp.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( temp.effectiveTemperatures()[2] ) );

  // no secondary scatterer => 0 secondary temperature
  CHECK( 0 == chunk.secondaryEffectiveTemperatures().size() );

  CHECK( 16 == chunk.NC() );
}

std::string chunkWithTwoTemperaturesAndOneScatterer() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 4.000000+2 0.000000+0          4          0          5          0  27 7  4     \n"
    " 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n"
    " 2.936000+2 3.952570-2          1          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 4.000000+2 3.952570-2          4          0          5          0  27 7  4     \n"
    " 6.921141-4 7.273641-4 7.644060-4 8.033305-4 8.442328-4             27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}

void verifyChunkWithTwoTemperaturesAndOneScatterer(
       const section::Type< 7, 4 >& chunk ) {

  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.sectionNumber() );

  CHECK( 127 == chunk.ZA() );
  CHECK( 127 == chunk.targetIdentifier() );
  CHECK_THAT( 8.934780e+0, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LAT() );
  CHECK( 1 == chunk.temperatureOption() );
  CHECK( 0 == chunk.LASYM() );
  CHECK( 0 == chunk.symmetryOption() );

  auto barray = chunk.constants();
  CHECK( 0 == barray.LLN() );
  CHECK( 0 == barray.sabStorageType() );
  CHECK( 6 == barray.NI() );
  CHECK( 6 == barray.numberConstants() );
  CHECK( 0 == barray.NS() );
  CHECK( 0 == barray.numberNonPrincipalScatterers() );

  CHECK_THAT( 1.976285e+2, WithinRel( barray.epsilon() ) );
  CHECK_THAT( 5.000001e+0, WithinRel( barray.upperEnergyLimit() ) );
  CHECK( 1 == barray.totalFreeCrossSections().size() );
  CHECK_THAT( 6.153875e+0, WithinRel( barray.totalFreeCrossSections()[0] ) );
  CHECK( 1 == barray.atomicWeightRatios().size() );
  CHECK_THAT( 8.934780e+0, WithinRel( barray.atomicWeightRatios()[0] ) );
  CHECK( 1 == barray.numberAtoms().size() );
  CHECK_THAT( 1., WithinRel( barray.numberAtoms()[0] ) );
  CHECK( 0 == barray.analyticalFunctionTypes().size() );

  auto table = std::get< TabulatedFunctions >( chunk.scatteringLaw() );
  CHECK( 1 == table.NR() );
  CHECK( 2 == table.NB() );
  CHECK( 2 == table.numberBetas() );
  CHECK( 1 == table.boundaries().size() );
  CHECK( 2 == table.boundaries()[0] );
  CHECK( 1 == table.interpolants().size() );
  CHECK( 4 == table.interpolants()[0] );

  CHECK( 2 == table.B().size() );
  CHECK( 2 == table.betas().size() );
  CHECK_THAT( 0.0, WithinRel( table.B()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.B()[1] ) );
  CHECK_THAT( 0.0, WithinRel( table.betas()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.betas()[1] ) );

  auto value = table.scatteringFunctions()[0];
  CHECK_THAT( 0.0, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 4 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386876e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508466e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 1.306574e-9, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 5.29573e-10, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 4.430020e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 4.655671e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 4.892796e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 4.510209e-8, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 2.183942e-8, WithinRel( value.thermalScatteringValues()[1][4] ) );

  value = table.scatteringFunctions()[1];
  CHECK_THAT( 3.952570e-2, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 2 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386694e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508273e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 2.770291e-4, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 2.911373e-4, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 6.921141e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 7.273641e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 7.644060e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 8.033305e-4, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 8.442328e-4, WithinRel( value.thermalScatteringValues()[1][4] ) );

  auto temp = chunk.principalEffectiveTemperature();
  CHECK( 3 == temp.NT() );
  CHECK( 3 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 3 == temp.boundaries()[0] );
  CHECK( 3 == temp.moderatorTemperatures().size() );
  CHECK( 3 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( temp.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( temp.effectiveTemperatures()[2] ) );

  // no secondary scatterer => 0 secondary temperature
  CHECK( 0 == chunk.secondaryEffectiveTemperatures().size() );

  CHECK( 20 == chunk.NC() );
}

std::string chunkWithTwoTemperaturesAndTwoScatterers() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0         12          1  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 4.000000+2 0.000000+0          4          0          5          0  27 7  4     \n"
    " 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n"
    " 2.936000+2 3.952570-2          1          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 4.000000+2 3.952570-2          4          0          5          0  27 7  4     \n"
    " 6.921141-4 7.273641-4 7.644060-4 8.033305-4 8.442328-4             27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          2                                              27 7  4     \n"
    " 2.936000+2 3.000000+2 1.200000+3 1.250000+3                        27 7  4     \n";
}

void verifyChunkWithTwoTemperaturesAndTwoScatterers(
       const section::Type< 7, 4 >& chunk ) {

  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.sectionNumber() );

  CHECK( 127 == chunk.ZA() );
  CHECK( 127 == chunk.targetIdentifier() );
  CHECK_THAT( 8.934780e+0, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LAT() );
  CHECK( 1 == chunk.temperatureOption() );
  CHECK( 0 == chunk.LASYM() );
  CHECK( 0 == chunk.symmetryOption() );

  auto barray = chunk.constants();
  CHECK( 0 == barray.LLN() );
  CHECK( 0 == barray.sabStorageType() );
  CHECK( 12 == barray.NI() );
  CHECK( 12 == barray.numberConstants() );
  CHECK( 1 == barray.NS() );
  CHECK( 1 == barray.numberNonPrincipalScatterers() );

  CHECK_THAT( 1.976285e+2, WithinRel( barray.epsilon() ) );
  CHECK_THAT( 5.000001e+0, WithinRel( barray.upperEnergyLimit() ) );
  CHECK( 2 == barray.totalFreeCrossSections().size() );
  CHECK_THAT( 6.153875e+0, WithinRel( barray.totalFreeCrossSections()[0] ) );
  CHECK_THAT( 3.748750e+0 , WithinRel( barray.totalFreeCrossSections()[1] ) );
  CHECK( 2 == barray.atomicWeightRatios().size() );
  CHECK_THAT( 8.934780e+0, WithinRel( barray.atomicWeightRatios()[0] ) );
  CHECK_THAT( 1.586200e+1, WithinRel( barray.atomicWeightRatios()[1] ) );
  CHECK( 2 == barray.numberAtoms().size() );
  CHECK_THAT( 1., WithinRel( barray.numberAtoms()[0] ) );
  CHECK_THAT( 2., WithinRel( barray.numberAtoms()[1] ) );
  CHECK( 1 == barray.analyticalFunctionTypes().size() );
  CHECK( 0 == barray.analyticalFunctionTypes()[0] );

  auto table = std::get< TabulatedFunctions >( chunk.scatteringLaw() );
  CHECK( 1 == table.NR() );
  CHECK( 2 == table.NB() );
  CHECK( 2 == table.numberBetas() );
  CHECK( 1 == table.boundaries().size() );
  CHECK( 2 == table.boundaries()[0] );
  CHECK( 1 == table.interpolants().size() );
  CHECK( 4 == table.interpolants()[0] );

  CHECK( 2 == table.B().size() );
  CHECK( 2 == table.betas().size() );
  CHECK_THAT( 0.0, WithinRel( table.B()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.B()[1] ) );
  CHECK_THAT( 0.0, WithinRel( table.betas()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.betas()[1] ) );

  auto value = table.scatteringFunctions()[0];
  CHECK_THAT( 0.0, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 4 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386876e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508466e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 1.306574e-9, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 5.29573e-10, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 4.430020e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 4.655671e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 4.892796e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 4.510209e-8, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 2.183942e-8, WithinRel( value.thermalScatteringValues()[1][4] ) );

  value = table.scatteringFunctions()[1];
  CHECK_THAT( 3.952570e-2, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 2 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386694e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508273e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 2.770291e-4, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 2.911373e-4, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 6.921141e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 7.273641e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 7.644060e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 8.033305e-4, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 8.442328e-4, WithinRel( value.thermalScatteringValues()[1][4] ) );

  auto temp = chunk.principalEffectiveTemperature();
  CHECK( 3 == temp.NT() );
  CHECK( 3 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 3 == temp.boundaries()[0] );
  CHECK( 3 == temp.moderatorTemperatures().size() );
  CHECK( 3 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( temp.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( temp.effectiveTemperatures()[2] ) );

  CHECK( 1 == chunk.secondaryEffectiveTemperatures().size() );

  temp = chunk.secondaryEffectiveTemperatures()[0].value();
  CHECK( 2 == temp.NT() );
  CHECK( 2 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 2 == temp.boundaries()[0] );
  CHECK( 2 == temp.moderatorTemperatures().size() );
  CHECK( 2 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 3.00e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 1.250e+3, WithinRel( temp.effectiveTemperatures()[1] ) );

  CHECK( 24 == chunk.NC() );
}

std::string chunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0         12          1  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 1.000000+0 3.748750+0 1.586200+1 0.000000+0 0.000000+0 2.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 4.000000+2 0.000000+0          4          0          5          0  27 7  4     \n"
    " 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n"
    " 2.936000+2 3.952570-2          1          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 4.000000+2 3.952570-2          4          0          5          0  27 7  4     \n"
    " 6.921141-4 7.273641-4 7.644060-4 8.033305-4 8.442328-4             27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n";
}

void verifyChunkWithTwoTemperaturesTwoScatterersAndNoSecondaryTemperature(
       const section::Type< 7, 4 >& chunk ) {

  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.sectionNumber() );

  CHECK( 127 == chunk.ZA() );
  CHECK( 127 == chunk.targetIdentifier() );
  CHECK_THAT( 8.934780e+0, WithinRel( chunk.AWR() ) );
  CHECK( 1 == chunk.LAT() );
  CHECK( 1 == chunk.temperatureOption() );
  CHECK( 0 == chunk.LASYM() );
  CHECK( 0 == chunk.symmetryOption() );

  auto barray = chunk.constants();
  CHECK( 0 == barray.LLN() );
  CHECK( 0 == barray.sabStorageType() );
  CHECK( 12 == barray.NI() );
  CHECK( 12 == barray.numberConstants() );
  CHECK( 1 == barray.NS() );
  CHECK( 1 == barray.numberNonPrincipalScatterers() );

  CHECK_THAT( 1.976285e+2, WithinRel( barray.epsilon() ) );
  CHECK_THAT( 5.000001e+0, WithinRel( barray.upperEnergyLimit() ) );
  CHECK( 2 == barray.totalFreeCrossSections().size() );
  CHECK_THAT( 6.153875e+0, WithinRel( barray.totalFreeCrossSections()[0] ) );
  CHECK_THAT( 3.748750e+0 , WithinRel( barray.totalFreeCrossSections()[1] ) );
  CHECK( 2 == barray.atomicWeightRatios().size() );
  CHECK_THAT( 8.934780e+0, WithinRel( barray.atomicWeightRatios()[0] ) );
  CHECK_THAT( 1.586200e+1, WithinRel( barray.atomicWeightRatios()[1] ) );
  CHECK( 2 == barray.numberAtoms().size() );
  CHECK_THAT( 1., WithinRel( barray.numberAtoms()[0] ) );
  CHECK_THAT( 2., WithinRel( barray.numberAtoms()[1] ) );
  CHECK( 1 == barray.analyticalFunctionTypes().size() );
  CHECK( 1 == barray.analyticalFunctionTypes()[0] );

  auto table = std::get< TabulatedFunctions >( chunk.scatteringLaw() );
  CHECK( 1 == table.NR() );
  CHECK( 2 == table.NB() );
  CHECK( 2 == table.numberBetas() );
  CHECK( 1 == table.boundaries().size() );
  CHECK( 2 == table.boundaries()[0] );
  CHECK( 1 == table.interpolants().size() );
  CHECK( 4 == table.interpolants()[0] );

  CHECK( 2 == table.B().size() );
  CHECK( 2 == table.betas().size() );
  CHECK_THAT( 0.0, WithinRel( table.B()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.B()[1] ) );
  CHECK_THAT( 0.0, WithinRel( table.betas()[0] ) );
  CHECK_THAT( 3.952570e-2, WithinRel( table.betas()[1] ) );

  auto value = table.scatteringFunctions()[0];
  CHECK_THAT( 0.0, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 4 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386876e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508466e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 1.306574e-9, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 5.29573e-10, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 4.430020e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 4.655671e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 4.892796e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 4.510209e-8, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 2.183942e-8, WithinRel( value.thermalScatteringValues()[1][4] ) );

  value = table.scatteringFunctions()[1];
  CHECK_THAT( 3.952570e-2, WithinRel( value.beta() ) );
  CHECK( 1 == value.LT() );
  CHECK( 1 == value.temperatureDependenceFlag() );
  CHECK( 2 == value.NT() );
  CHECK( 2 == value.numberTemperatures() );

  CHECK( 1 == value.NR() );
  CHECK( 5 == value.NA() );
  CHECK( 5 == value.numberAlphas() );
  CHECK( 1 == value.boundaries().size() );
  CHECK( 5 == value.boundaries()[0] );
  CHECK( 1 == value.interpolants().size() );
  CHECK( 2 == value.interpolants()[0] );

  CHECK( 2 == value.temperatures().size() );
  CHECK_THAT( 293.6, WithinRel( value.temperatures()[0] ) );
  CHECK_THAT( 400.0, WithinRel( value.temperatures()[1] ) );

  CHECK( 5 == value.alphas().size() );
  CHECK_THAT( 4.423802e-3, WithinRel( value.alphas()[0] ) );
  CHECK_THAT( 4.649528e-3, WithinRel( value.alphas()[1] ) );
  CHECK_THAT( 4.886772e-3, WithinRel( value.alphas()[2] ) );
  CHECK_THAT( 8.418068e+1, WithinRel( value.alphas()[3] ) );
  CHECK_THAT( 8.847604e+1, WithinRel( value.alphas()[4] ) );

  CHECK( 1 == value.LI().size() );
  CHECK( 4 == value.LI()[0] );
  CHECK( 1 == value.temperatureInterpolants().size() );
  CHECK( 4 == value.temperatureInterpolants()[0] );

  CHECK( 2 == value.thermalScatteringValues().size() );
  CHECK( 5 == value.thermalScatteringValues()[0].size() );
  CHECK_THAT( 2.386694e-4, WithinRel( value.thermalScatteringValues()[0][0] ) );
  CHECK_THAT( 2.508273e-4, WithinRel( value.thermalScatteringValues()[0][1] ) );
  CHECK_THAT( 2.636238e-4, WithinRel( value.thermalScatteringValues()[0][2] ) );
  CHECK_THAT( 2.770291e-4, WithinRel( value.thermalScatteringValues()[0][3] ) );
  CHECK_THAT( 2.911373e-4, WithinRel( value.thermalScatteringValues()[0][4] ) );
  CHECK( 5 == value.thermalScatteringValues()[1].size() );
  CHECK_THAT( 6.921141e-4, WithinRel( value.thermalScatteringValues()[1][0] ) );
  CHECK_THAT( 7.273641e-4, WithinRel( value.thermalScatteringValues()[1][1] ) );
  CHECK_THAT( 7.644060e-4, WithinRel( value.thermalScatteringValues()[1][2] ) );
  CHECK_THAT( 8.033305e-4, WithinRel( value.thermalScatteringValues()[1][3] ) );
  CHECK_THAT( 8.442328e-4, WithinRel( value.thermalScatteringValues()[1][4] ) );

  auto temp = chunk.principalEffectiveTemperature();
  CHECK( 3 == temp.NT() );
  CHECK( 3 == temp.numberTemperatures() );
  CHECK( 1 == temp.NR() );
  CHECK( 1 == temp.interpolants().size() );
  CHECK( 1 == temp.boundaries().size() );
  CHECK( 2 == temp.interpolants()[0] );
  CHECK( 3 == temp.boundaries()[0] );
  CHECK( 3 == temp.moderatorTemperatures().size() );
  CHECK( 3 == temp.effectiveTemperatures().size() );
  CHECK_THAT( 293.6, WithinRel( temp.moderatorTemperatures()[0] ) );
  CHECK_THAT( 600., WithinRel( temp.moderatorTemperatures()[1] ) );
  CHECK_THAT( 1200., WithinRel( temp.moderatorTemperatures()[2] ) );
  CHECK_THAT( 5.332083e+2, WithinRel( temp.effectiveTemperatures()[0] ) );
  CHECK_THAT( 7.354726e+2, WithinRel( temp.effectiveTemperatures()[1] ) );
  CHECK_THAT( 1.270678e+3, WithinRel( temp.effectiveTemperatures()[2] ) );

  // one secondary scatterer => 1 secondary temperature (std::nullopt in this
  // case)
  CHECK( 1 == chunk.secondaryEffectiveTemperatures().size() );
  CHECK( std::nullopt == chunk.secondaryEffectiveTemperatures()[0] );

  CHECK( 21 == chunk.NC() );
}

std::string chunkWithInvalidLAT() {
  return
    " 1.270000+2 8.934780+0          0          2          0          0  27 7  4     \n"
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

std::string chunkWithInvalidLASYM() {
  return
    " 1.270000+2 8.934780+0          0          2          0          0  27 7  4     \n"
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
