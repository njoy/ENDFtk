#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/12.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using Multiplicities = section::Type< 12 >::Multiplicities;
using PartialMultiplicity = section::Type< 12 >::PartialMultiplicity;
using TotalMultiplicity = section::Type< 12 >::TotalMultiplicity;

std::string chunkWithOnePartial();
void verifyChunkWithOnePartial( const Multiplicities& );
std::string chunkWithMultiplePartials();
void verifyChunkWithMultiplePartials( const Multiplicities& );
std::string invalidChunk();

SCENARIO( "Multiplicities" ) {

  GIVEN( "valid data for a Multiplicities with one partial" ) {

    std::string string = chunkWithOnePartial();

    WHEN( "the data is given explicitly" ) {

      PartialMultiplicity partial = { 0.0, 0.0, 0, 1,
                                      { 2 }, { 2 },
                                      { 1e-5, 3e+7 },
                                      { 8.579050e+0, 1.487778e+1 } };

      Multiplicities chunk( std::move( partial ) );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOnePartial( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Multiplicities chunk( begin, end, lineNumber, 9228, 12, 18, 1 );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithOnePartial( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a Multiplicities with one total and multiple "
         "partials" ) {

    std::string string = chunkWithMultiplePartials();

    WHEN( "the data is given explicitly" ) {

      TotalMultiplicity total = { { 2 }, { 2 }, { 1e-5, 3e+7 }, { 10., 15. } };

      std::vector< PartialMultiplicity > partials =
        { { 0.0, 0.0, 0, 1,
            { 2 }, { 2 }, { 1e-5, 3e+7 }, { 8.579050e+0, 1.487778e+1 } },
          { 0.0, 0.0, 0, 1,
            { 2 }, { 2 }, { 1e-5, 3e+7 }, { 1.420950e+0, 1.222200e-1 } } };

      Multiplicities chunk( std::move( total ), std::move( partials ) );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithMultiplePartials( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      Multiplicities chunk( begin, end, lineNumber, 9228, 12, 18, 2 );

      THEN( "a Multiplicities can be constructed and members can be "
            "tested" ) {

        verifyChunkWithMultiplePartials( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 12, 18 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Multiplicities" ) {

   WHEN( "no partials are given" ) {

     THEN( "an exception is thrown" ) {

       CHECK_THROWS( Multiplicities(
                         TotalMultiplicity( { 2 }, { 2 },
                                            { 1e-5, 3e+7 },
                                            { 10., 15. } ),
                         {} ) );
     }
   }
  }
} // SCENARIO

std::string chunkWithOnePartial() {
  return
  " 0.000000+0 0.000000+0          0          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}

void verifyChunkWithOnePartial( const Multiplicities& chunk ) {

  CHECK( std::nullopt == chunk.totalMultiplicity() );
  CHECK( 1 == chunk.photonPartialMultiplicities().size() );

  CHECK( 1 == chunk.NK() );
  CHECK( 1 == chunk.numberPhotons() );
  CHECK( 1 == chunk.LO() );
  CHECK( 1 == chunk.representation() );

  auto partial = chunk.photonPartialMultiplicities()[0];
  CHECK( 0.0 == Approx( partial.EG() ) );
  CHECK( 0.0 == Approx( partial.photonOrBindingEnergy() ) );
  CHECK( 0.0 == Approx( partial.ES() ) );
  CHECK( 0.0 == Approx( partial.levelEnergy() ) );
  CHECK( 0 == partial.LP() );
  CHECK( 0 == partial.primaryPhotonFlag() );
  CHECK( 1 == partial.LF() );
  CHECK( 1 == partial.LAW() );
  CHECK( 2 == partial.NP() );
  CHECK( 1 == partial.NR() );
  CHECK( 1 == partial.interpolants().size() );
  CHECK( 1 == partial.boundaries().size() );
  CHECK( 2 == partial.interpolants()[0] );
  CHECK( 2 == partial.boundaries()[0] );
  CHECK( 2 == partial.energies().size() );
  CHECK( 2 == partial.multiplicities().size() );
  CHECK( 1e-5 == Approx( partial.energies()[0] ) );
  CHECK( 3e+7 == Approx( partial.energies()[1] ) );
  CHECK( 8.579050e+0 == Approx( partial.multiplicities()[0] ) );
  CHECK( 1.487778e+1 == Approx( partial.multiplicities()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string chunkWithMultiplePartials() {
  return
  " 0.000000+0 0.000000+0          0          0          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 1.000000+1 3.000000+7 1.500000+1                      922812 18     \n"
  " 0.000000+0 0.000000+0          0          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n"
  " 0.000000+0 0.000000+0          0          1          1          2922812 18     \n"
  "          2          2                                            922812 18     \n"
  " 1.000000-5 1.420950+0 3.000000+7 1.222200-1                      922812 18     \n";
}

void verifyChunkWithMultiplePartials( const Multiplicities& chunk ) {

  CHECK( std::nullopt != chunk.totalMultiplicity() );
  CHECK( 2 == chunk.photonPartialMultiplicities().size() );
  CHECK( 2 == chunk.NK() );
  CHECK( 2 == chunk.numberPhotons() );
  CHECK( 1 == chunk.LO() );
  CHECK( 1 == chunk.representation() );

  auto total = chunk.totalMultiplicity().value();
  CHECK( 2 == total.NP() );
  CHECK( 1 == total.NR() );
  CHECK( 1 == total.interpolants().size() );
  CHECK( 1 == total.boundaries().size() );
  CHECK( 2 == total.interpolants()[0] );
  CHECK( 2 == total.boundaries()[0] );
  CHECK( 2 == total.energies().size() );
  CHECK( 2 == total.multiplicities().size() );
  CHECK( 1e-5 == Approx( total.energies()[0] ) );
  CHECK( 3e+7 == Approx( total.energies()[1] ) );
  CHECK( 10. == Approx( total.multiplicities()[0] ) );
  CHECK( 15. == Approx( total.multiplicities()[1] ) );

  auto partial = chunk.photonPartialMultiplicities()[0];
  CHECK( 0.0 == Approx( partial.EG() ) );
  CHECK( 0.0 == Approx( partial.photonOrBindingEnergy() ) );
  CHECK( 0.0 == Approx( partial.ES() ) );
  CHECK( 0.0 == Approx( partial.levelEnergy() ) );
  CHECK( 0 == partial.LP() );
  CHECK( 0 == partial.primaryPhotonFlag() );
  CHECK( 1 == partial.LF() );
  CHECK( 1 == partial.LAW() );
  CHECK( 2 == partial.NP() );
  CHECK( 1 == partial.NR() );
  CHECK( 1 == partial.interpolants().size() );
  CHECK( 1 == partial.boundaries().size() );
  CHECK( 2 == partial.interpolants()[0] );
  CHECK( 2 == partial.boundaries()[0] );
  CHECK( 2 == partial.energies().size() );
  CHECK( 2 == partial.multiplicities().size() );
  CHECK( 1e-5 == Approx( partial.energies()[0] ) );
  CHECK( 3e+7 == Approx( partial.energies()[1] ) );
  CHECK( 8.579050e+0 == Approx( partial.multiplicities()[0] ) );
  CHECK( 1.487778e+1 == Approx( partial.multiplicities()[1] ) );

  partial = chunk.photonPartialMultiplicities()[1];
  CHECK( 0.0 == Approx( partial.EG() ) );
  CHECK( 0.0 == Approx( partial.photonOrBindingEnergy() ) );
  CHECK( 0.0 == Approx( partial.ES() ) );
  CHECK( 0.0 == Approx( partial.levelEnergy() ) );
  CHECK( 0 == partial.LP() );
  CHECK( 0 == partial.primaryPhotonFlag() );
  CHECK( 1 == partial.LF() );
  CHECK( 1 == partial.LAW() );
  CHECK( 2 == partial.NP() );
  CHECK( 1 == partial.NR() );
  CHECK( 1 == partial.interpolants().size() );
  CHECK( 1 == partial.boundaries().size() );
  CHECK( 2 == partial.interpolants()[0] );
  CHECK( 2 == partial.boundaries()[0] );
  CHECK( 2 == partial.energies().size() );
  CHECK( 2 == partial.multiplicities().size() );
  CHECK( 1e-5 == Approx( partial.energies()[0] ) );
  CHECK( 3e+7 == Approx( partial.energies()[1] ) );
  CHECK( 1.420950e+0 == Approx( partial.multiplicities()[0] ) );
  CHECK( 1.222200e-1 == Approx( partial.multiplicities()[1] ) );

  CHECK( 9 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 0.000000+0          0          1          2          2922812 18     \n"
    "          2          2                                            922812 18     \n"
    " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n";
}
