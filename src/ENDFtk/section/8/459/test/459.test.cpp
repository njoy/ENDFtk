// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/8/459.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using FissionYieldData = section::FissionYieldData;

// macros don't like multiple template arguments
using section8459 = section::Type< 8, 459 >;

std::string chunk();
void verifyChunk( const section::Type< 8, 459 >& );
std::string chunkWithEnergyIndependentYields();
void verifyChunkWithEnergyIndependentYields( const section::Type< 8, 459 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 8, 459 >" ) {

  GIVEN( "valid data for a section::Type< 8, 459 > for energy dependent yields" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly as arrays" ) {

      int zaid = 92235;
      double awr = 233.0250;

      std::vector< unsigned int > identifiers = { 23066, 54135, 72171 };
      std::vector< unsigned int > states = { 0, 0, 0 };

      std::vector< double > energies = { 0.0253, 500e+3 };
      std::vector< unsigned int > interpolants = { 3 };

      std::vector< std::vector< std::array< double, 2 > > > yields = {

        { {{ 2.05032e-19, 1.31220e-19 }}, {{ 4.48456e-18, 2.87012e-18 }} }, // 230660
        { {{ 7.851250e-4, 4.710750e-5 }}, {{ 1.196100e-3, 2.751030e-4 }} }, // 541350
        { {{ 0, 0 }}, {{ 0, 0 }} }                                          // 721710
      };

      section::Type< 8, 459 > chunk( zaid, awr,
                                     std::move( identifiers ),
                                     std::move( states ),
                                     std::move( energies ),
                                     std::move( interpolants ),
                                     std::move( yields ) );

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly as a FissionYieldData array" ) {

      int zaid = 92235.;
      double awr = 233.0250;

      std::vector< FissionYieldData > yields = {

        FissionYieldData( { 23066, 54135, 72171 }, { 0, 0, 0 },
                          { {{ 2.05032e-19, 1.31220e-19 }},
                            {{ 7.851250e-4, 4.710750e-5 }},
                            {{ 0, 0 }} },
                          0.0253, 1 ),
        FissionYieldData( { 23066, 54135, 72171 }, { 0, 0, 0 },
                          { {{ 4.48456e-18, 2.87012e-18 }},
                            {{ 1.196100e-3, 2.751030e-4 }},
                            {{ 0, 0 }} },
                          500e+3, 3 ) };

      section::Type< 8, 459 > chunk( zaid, awr,
                                     std::move( yields ) );

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 8, 459 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 8, 459, std::string( sectionString ) );

      section::Type< 8, 459 > chunk = section.parse< 8, 459 >();

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 8, 459 > for energy independent yields" ) {

    std::string sectionString = chunkWithEnergyIndependentYields() + validSEND();

    WHEN( "the data is given explicitly using arrays" ) {

      int zaid = 92235;
      double awr = 233.0250;

      std::vector< unsigned int > identifiers = { 23066, 54135, 72171 };
      std::vector< unsigned int > states = { 0, 0, 0 };

      std::vector< std::array< double, 2 > > yields = {

        {{ 2.05032e-19, 1.31220e-19 }},
        {{ 7.851250e-4, 4.710750e-5 }},
        {{ 0, 0 }}
      };

      section::Type< 8, 459 > chunk( zaid, awr,
                                     std::move( identifiers ),
                                     std::move( states ),
                                     std::move( yields ) );

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithEnergyIndependentYields( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 8, 459 > chunk( head, begin, end, lineNumber, 9228 );

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithEnergyIndependentYields( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9228, 8, 459, std::string( sectionString ) );

      section::Type< 8, 459 > chunk = section.parse< 8, 459 >();

      THEN( "a section::Type< 8, 459 > can be constructed and members can be "
            "tested" ) {

        verifyChunkWithEnergyIndependentYields( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 8 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 8, 459 >" ) {

    WHEN( "a string representation of a valid section::Type< 8, 459 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section8459( head, begin, end, lineNumber, 9228 ) );
      } // THEN
    } // WHEN

    WHEN( "the number of identifiers, isomeric states and yield sets are "
          "inconsistent" ) {

      int zaid = 92235;
      double awr = 233.0250;

      std::vector< unsigned int > wrong = { 23066, 54135 };
      std::vector< unsigned int > states = { 0, 0, 0 };

      std::vector< double > energies = { 0.0253, 500e+3 };
      std::vector< unsigned int > interpolants = { 3 };

      std::vector< std::vector< std::array< double, 2 > > > yields = {

        { {{ 2.05032e-19, 1.31220e-19 }}, {{ 4.48456e-18, 2.87012e-18 }} }, // 230660
        { {{ 7.851250e-4, 4.710750e-5 }}, {{ 1.196100e-3, 2.751030e-4 }} }, // 541350
        { {{ 0, 0 }}, {{ 0, 0 }} }                                          // 721710
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section8459( zaid, awr,
                                   std::move( wrong ),
                                   std::move( states ),
                                   std::move( energies ),
                                   std::move( interpolants ),
                                   std::move( yields ) ) );
      } // THEN
    } // WHEN

    WHEN( "the number of identifiers, isomeric states and yield sets are "
          "inconsistent" ) {

      int zaid = 92235;
      double awr = 233.0250;

      std::vector< unsigned int > identifiers = { 23066, 54135, 72171 };
      std::vector< unsigned int > states = { 0, 0, 0 };

      std::vector< double > energies = { 0.0253, 500e+3 };
      std::vector< unsigned int > interpolants = { 3 };

      std::vector< std::vector< std::array< double, 2 > > > wrong = {

        { {{ 2.05032e-19, 1.31220e-19 }}, {{ 4.48456e-18, 2.87012e-18 }} }, // 230660
        { {{ 1.196100e-3, 2.751030e-4 }} }, // 541350 missing one pair
        { {{ 0, 0 }}, {{ 0, 0 }} }                                          // 721710
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( section8459( zaid, awr,
                                   std::move( identifiers ),
                                   std::move( states ),
                                   std::move( energies ),
                                   std::move( interpolants ),
                                   std::move( wrong ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return

    " 9.223500+4 2.330250+2          2          0          0          09228 8459     \n"
    " 2.530000-2 0.000000+0          1          0         12          39228 8459     \n"
    " 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8459     \n"
    " 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n"
    " 5.000000+5 0.000000+0          3          0         12          39228 8459     \n"
    " 2.306600+4 0.000000+0 4.48456-18 2.87012-18 5.413500+4 0.000000+09228 8459     \n"
    " 1.196100-3 2.751030-4 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n";
}

void verifyChunk( const section::Type< 8, 459 >& chunk ) {

  CHECK( 459 == chunk.MT() );
  CHECK( 459 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK( 92235 == chunk.targetIdentifier() );
  CHECK_THAT( 233.0250, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 233.0250, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( false == chunk.LE() );
  CHECK( false == chunk.isEnergyIndependent() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberIncidentEnergies() );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK_THAT( 0.0253, WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 500e+3, WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 0.0253, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 500e+3, WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK( 2 == chunk.yields().size() );

  auto data = chunk.yields()[0];
  CHECK( 1 == data.I() );
  CHECK( 1 == data.interpolationType() );
  CHECK( false == data.LE() );
  CHECK( false == data.isEnergyIndependent() );
  CHECK( 3 == data.NFP() );
  CHECK( 3 == data.numberFissionProducts() );
  CHECK_THAT( 0.0253, WithinRel( data.E() ) );
  CHECK_THAT( 0.0253, WithinRel( data.incidentEnergy() ) );

  CHECK( 3 == data.fissionProducts().size() );
  CHECK( 23066 == data.fissionProducts()[0].ZAFP() );
  CHECK( 54135 == data.fissionProducts()[1].ZAFP() );
  CHECK( 72171 == data.fissionProducts()[2].ZAFP() );
  CHECK( 23066 == data.fissionProducts()[0].fissionProductIdentifier() );
  CHECK( 54135 == data.fissionProducts()[1].fissionProductIdentifier() );
  CHECK( 72171 == data.fissionProducts()[2].fissionProductIdentifier() );
  CHECK( 0 == data.fissionProducts()[0].FPS() );
  CHECK( 0 == data.fissionProducts()[1].FPS() );
  CHECK( 0 == data.fissionProducts()[2].FPS() );
  CHECK( 0 == data.fissionProducts()[0].isomericState() );
  CHECK( 0 == data.fissionProducts()[1].isomericState() );
  CHECK( 0 == data.fissionProducts()[2].isomericState() );
  CHECK_THAT( 2.05032e-19, WithinRel( data.fissionProducts()[0].Y()[0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.fissionProducts()[0].Y()[1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.fissionProducts()[1].Y()[0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.fissionProducts()[1].Y()[1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[1] ) );

  CHECK( 3 == data.ZAFP().size() );
  CHECK( 3 == data.fissionProductIdentifiers().size() );
  CHECK( 3 == data.FPS().size() );
  CHECK( 3 == data.isomericStates().size() );
  CHECK( 3 == data.Y().size() );
  CHECK( 3 == data.fissionYields().size() );
  CHECK( 23066 == data.ZAFP()[0] );
  CHECK( 54135 == data.ZAFP()[1] );
  CHECK( 72171 == data.ZAFP()[2] );
  CHECK( 23066 == data.fissionProductIdentifiers()[0] );
  CHECK( 54135 == data.fissionProductIdentifiers()[1] );
  CHECK( 72171 == data.fissionProductIdentifiers()[2] );
  CHECK( 0 == data.FPS()[0] );
  CHECK( 0 == data.FPS()[1] );
  CHECK( 0 == data.FPS()[2] );
  CHECK( 0 == data.isomericStates()[0] );
  CHECK( 0 == data.isomericStates()[1] );
  CHECK( 0 == data.isomericStates()[2] );
  CHECK( 2 == data.Y()[0].size() );
  CHECK( 2 == data.Y()[1].size() );
  CHECK( 2 == data.Y()[2].size() );
  CHECK( 2 == data.fissionYields()[0].size() );
  CHECK( 2 == data.fissionYields()[1].size() );
  CHECK( 2 == data.fissionYields()[2].size() );
  CHECK_THAT( 2.05032e-19, WithinRel( data.Y()[0][0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.Y()[0][1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.Y()[1][0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.Y()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][1] ) );
  CHECK_THAT( 2.05032e-19, WithinRel( data.fissionYields()[0][0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.fissionYields()[0][1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.fissionYields()[1][0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.fissionYields()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][1] ) );

  data = chunk.yields()[1];
  CHECK( 3 == data.I() );
  CHECK( 3 == data.interpolationType() );
  CHECK( false == data.LE() );
  CHECK( false == data.isEnergyIndependent() );
  CHECK( 3 == data.NFP() );
  CHECK( 3 == data.numberFissionProducts() );
  CHECK_THAT( 500e+3, WithinRel( data.E() ) );
  CHECK_THAT( 500e+3, WithinRel( data.incidentEnergy() ) );

  CHECK( 3 == data.fissionProducts().size() );
  CHECK( 23066 == data.fissionProducts()[0].ZAFP() );
  CHECK( 54135 == data.fissionProducts()[1].ZAFP() );
  CHECK( 72171 == data.fissionProducts()[2].ZAFP() );
  CHECK( 23066 == data.fissionProducts()[0].fissionProductIdentifier() );
  CHECK( 54135 == data.fissionProducts()[1].fissionProductIdentifier() );
  CHECK( 72171 == data.fissionProducts()[2].fissionProductIdentifier() );
  CHECK( 0 == data.fissionProducts()[0].FPS() );
  CHECK( 0 == data.fissionProducts()[1].FPS() );
  CHECK( 0 == data.fissionProducts()[2].FPS() );
  CHECK( 0 == data.fissionProducts()[0].isomericState() );
  CHECK( 0 == data.fissionProducts()[1].isomericState() );
  CHECK( 0 == data.fissionProducts()[2].isomericState() );
  CHECK_THAT( 4.48456e-18, WithinRel( data.fissionProducts()[0].Y()[0] ) );
  CHECK_THAT( 2.87012e-18, WithinRel( data.fissionProducts()[0].Y()[1] ) );
  CHECK_THAT( 1.196100e-3, WithinRel( data.fissionProducts()[1].Y()[0] ) );
  CHECK_THAT( 2.751030e-4, WithinRel( data.fissionProducts()[1].Y()[1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[1] ) );

  CHECK( 3 == data.ZAFP().size() );
  CHECK( 3 == data.fissionProductIdentifiers().size() );
  CHECK( 3 == data.FPS().size() );
  CHECK( 3 == data.isomericStates().size() );
  CHECK( 3 == data.Y().size() );
  CHECK( 3 == data.fissionYields().size() );
  CHECK( 23066 == data.ZAFP()[0] );
  CHECK( 54135 == data.ZAFP()[1] );
  CHECK( 72171 == data.ZAFP()[2] );
  CHECK( 23066 == data.fissionProductIdentifiers()[0] );
  CHECK( 54135 == data.fissionProductIdentifiers()[1] );
  CHECK( 72171 == data.fissionProductIdentifiers()[2] );
  CHECK( 0 == data.FPS()[0] );
  CHECK( 0 == data.FPS()[1] );
  CHECK( 0 == data.FPS()[2] );
  CHECK( 0 == data.isomericStates()[0] );
  CHECK( 0 == data.isomericStates()[1] );
  CHECK( 0 == data.isomericStates()[2] );
  CHECK( 2 == data.Y()[0].size() );
  CHECK( 2 == data.Y()[1].size() );
  CHECK( 2 == data.Y()[2].size() );
  CHECK( 2 == data.fissionYields()[0].size() );
  CHECK( 2 == data.fissionYields()[1].size() );
  CHECK( 2 == data.fissionYields()[2].size() );
  CHECK_THAT( 4.48456e-18, WithinRel( data.Y()[0][0] ) );
  CHECK_THAT( 2.87012e-18, WithinRel( data.Y()[0][1] ) );
  CHECK_THAT( 1.196100e-3, WithinRel( data.Y()[1][0] ) );
  CHECK_THAT( 2.751030e-4, WithinRel( data.Y()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][1] ) );
  CHECK_THAT( 4.48456e-18, WithinRel( data.fissionYields()[0][0] ) );
  CHECK_THAT( 2.87012e-18, WithinRel( data.fissionYields()[0][1] ) );
  CHECK_THAT( 1.196100e-3, WithinRel( data.fissionYields()[1][0] ) );
  CHECK_THAT( 2.751030e-4, WithinRel( data.fissionYields()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string chunkWithEnergyIndependentYields() {
  return

    " 9.223500+4 2.330250+2          1          0          0          09228 8459     \n"
    " 0.000000+0 0.000000+0          0          0         12          39228 8459     \n"
    " 2.306600+4 0.000000+0 2.05032-19 1.31220-19 5.413500+4 0.000000+09228 8459     \n"
    " 7.851250-4 4.710750-5 7.217100+4 0.000000+0 0.000000+0 0.000000+09228 8459     \n";
}

void verifyChunkWithEnergyIndependentYields( const section::Type< 8, 459 >& chunk ) {

  CHECK( 459 == chunk.MT() );
  CHECK( 459 == chunk.sectionNumber() );

  CHECK( 92235 == chunk.ZA() );
  CHECK_THAT( 233.0250, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 233.0250, WithinRel( chunk.atomicWeightRatio() ) );

  CHECK( true == chunk.LE() );
  CHECK( true == chunk.isEnergyIndependent() );

  CHECK( 1 == chunk.NE() );
  CHECK( 1 == chunk.E().size() );
  CHECK( 1 == chunk.incidentEnergies().size() );
  CHECK_THAT( 0., WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.incidentEnergies()[0] ) );

  CHECK( 1 == chunk.yields().size() );

  auto data = chunk.yields()[0];
  CHECK( 0 == data.I() );
  CHECK( 0 == data.interpolationType() );
  CHECK( true == data.LE() );
  CHECK( true == data.isEnergyIndependent() );
  CHECK( 3 == data.NFP() );
  CHECK( 3 == data.numberFissionProducts() );
  CHECK_THAT( 0., WithinRel( data.E() ) );
  CHECK_THAT( 0., WithinRel( data.incidentEnergy() ) );

  CHECK( 3 == data.fissionProducts().size() );
  CHECK( 23066 == data.fissionProducts()[0].ZAFP() );
  CHECK( 54135 == data.fissionProducts()[1].ZAFP() );
  CHECK( 72171 == data.fissionProducts()[2].ZAFP() );
  CHECK( 23066 == data.fissionProducts()[0].fissionProductIdentifier() );
  CHECK( 54135 == data.fissionProducts()[1].fissionProductIdentifier() );
  CHECK( 72171 == data.fissionProducts()[2].fissionProductIdentifier() );
  CHECK( 0 == data.fissionProducts()[0].FPS() );
  CHECK( 0 == data.fissionProducts()[1].FPS() );
  CHECK( 0 == data.fissionProducts()[2].FPS() );
  CHECK( 0 == data.fissionProducts()[0].isomericState() );
  CHECK( 0 == data.fissionProducts()[1].isomericState() );
  CHECK( 0 == data.fissionProducts()[2].isomericState() );
  CHECK_THAT( 2.05032e-19, WithinRel( data.fissionProducts()[0].Y()[0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.fissionProducts()[0].Y()[1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.fissionProducts()[1].Y()[0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.fissionProducts()[1].Y()[1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionProducts()[2].Y()[1] ) );

  CHECK( 3 == data.ZAFP().size() );
  CHECK( 3 == data.fissionProductIdentifiers().size() );
  CHECK( 3 == data.FPS().size() );
  CHECK( 3 == data.isomericStates().size() );
  CHECK( 3 == data.Y().size() );
  CHECK( 3 == data.fissionYields().size() );
  CHECK( 23066 == data.ZAFP()[0] );
  CHECK( 54135 == data.ZAFP()[1] );
  CHECK( 72171 == data.ZAFP()[2] );
  CHECK( 23066 == data.fissionProductIdentifiers()[0] );
  CHECK( 54135 == data.fissionProductIdentifiers()[1] );
  CHECK( 72171 == data.fissionProductIdentifiers()[2] );
  CHECK( 0 == data.FPS()[0] );
  CHECK( 0 == data.FPS()[1] );
  CHECK( 0 == data.FPS()[2] );
  CHECK( 0 == data.isomericStates()[0] );
  CHECK( 0 == data.isomericStates()[1] );
  CHECK( 0 == data.isomericStates()[2] );
  CHECK( 2 == data.Y()[0].size() );
  CHECK( 2 == data.Y()[1].size() );
  CHECK( 2 == data.Y()[2].size() );
  CHECK( 2 == data.fissionYields()[0].size() );
  CHECK( 2 == data.fissionYields()[1].size() );
  CHECK( 2 == data.fissionYields()[2].size() );
  CHECK_THAT( 2.05032e-19, WithinRel( data.Y()[0][0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.Y()[0][1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.Y()[1][0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.Y()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.Y()[2][1] ) );
  CHECK_THAT( 2.05032e-19, WithinRel( data.fissionYields()[0][0] ) );
  CHECK_THAT( 1.31220e-19, WithinRel( data.fissionYields()[0][1] ) );
  CHECK_THAT( 7.851250e-4, WithinRel( data.fissionYields()[1][0] ) );
  CHECK_THAT( 4.710750e-5, WithinRel( data.fissionYields()[1][1] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][0] ) );
  CHECK_THAT( 0, WithinRel( data.fissionYields()[2][1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string validSEND() {
  return
    "                                                                  9228 8  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 8  4     \n";
}
