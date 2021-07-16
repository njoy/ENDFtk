#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/28.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SubshellData = section::Type< 28 >::SubshellData;

std::string chunk();
void verifyChunk( const SubshellData& );
std::string invalidChunk();

SCENARIO( "SubshellData" ) {

  GIVEN( "valid data for a SubshellData" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int subshell = 1;
      double energy = 11561;
      unsigned int eln = 2;
      std::vector< unsigned int > secondary = { 3, 4 };
      std::vector< unsigned int > tertiary = { 2, 3 };
      std::vector< double > energies = { 9.5066e+4, 9.8928e+4 };
      std::vector< double > probabilities = { 0.75, 0.25 };

      SubshellData chunk( subshell, energy, eln,
                          std::move( secondary ), std::move( tertiary ),
                          std::move( energies ), std::move( probabilities ) );

      THEN( "an SubshellData can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 28, 533 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      SubshellData chunk( begin, end, lineNumber, 100, 28, 533 );

      THEN( "a SubshellData can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 100, 28, 533 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a SubshellData" ) {

    WHEN( "a string representation with an error is given" ) {

      // NPL != 6*NTR+6
      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( SubshellData( begin, end, lineNumber, 100, 28, 533 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 0.000000+0          0          0         18          2 10028533     \n"
    " 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n"
    " 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n"
    " 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n";
}

void verifyChunk( const SubshellData& chunk ) {

  CHECK( 1 == chunk.SUBI() );
  CHECK( 1 == chunk.subshellDesignator() );
  CHECK( 2 == chunk.NTR() );
  CHECK( 2 == chunk.numberTransitions() );

  CHECK( 1.156100e+4 == Approx( chunk.EBI() ) );
  CHECK( 1.156100e+4 == Approx( chunk.subshellBindingEnergy() ) );
  CHECK( 2 == chunk.ELN() );
  CHECK( 2 == chunk.numberSubshellElectrons() );

  CHECK( 2 == chunk.transitions().size() );
  CHECK( 3 == chunk.transitions()[0].SUBJ() );
  CHECK( 4 == chunk.transitions()[1].SUBJ() );
  CHECK( 2 == chunk.transitions()[0].SUBK() );
  CHECK( 3 == chunk.transitions()[1].SUBK() );
  CHECK( 9.5066e+4 == Approx( chunk.transitions()[0].ETR() ) );
  CHECK( 9.8928e+4 == Approx( chunk.transitions()[1].ETR() ) );
  CHECK( 0.75 == Approx( chunk.transitions()[0].FTR() ) );
  CHECK( 0.25 == Approx( chunk.transitions()[1].FTR() ) );

  CHECK( 2 == chunk.SUBJ().size() );
  CHECK( 2 == chunk.secondarySubshellDesignators().size() );
  CHECK( 2 == chunk.SUBK().size() );
  CHECK( 2 == chunk.tertiarySubshellDesignators().size() );
  CHECK( 2 == chunk.ETR().size() );
  CHECK( 2 == chunk.transitionEnergies().size() );
  CHECK( 2 == chunk.FTR().size() );
  CHECK( 2 == chunk.transitionProbabilities().size() );

  CHECK( 3 == chunk.SUBJ()[0] );
  CHECK( 4 == chunk.SUBJ()[1] );
  CHECK( 3 == chunk.secondarySubshellDesignators()[0] );
  CHECK( 4 == chunk.secondarySubshellDesignators()[1] );
  CHECK( 2 == chunk.SUBK()[0] );
  CHECK( 3 == chunk.SUBK()[1] );
  CHECK( 2 == chunk.tertiarySubshellDesignators()[0] );
  CHECK( 3 == chunk.tertiarySubshellDesignators()[1] );
  CHECK( 9.5066e+4 == Approx( chunk.ETR()[0] ) );
  CHECK( 9.8928e+4 == Approx( chunk.ETR()[1] ) );
  CHECK( 9.5066e+4 == Approx( chunk.transitionEnergies()[0] ) );
  CHECK( 9.8928e+4 == Approx( chunk.transitionEnergies()[1] ) );
  CHECK( .75 == Approx( chunk.FTR()[0] ) );
  CHECK( .25 == Approx( chunk.FTR()[1] ) );
  CHECK( .75 == Approx( chunk.transitionProbabilities()[0] ) );
  CHECK( .25 == Approx( chunk.transitionProbabilities()[1] ) );

  CHECK( 4 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 1.000000+0 0.000000+0          0          0         18          1 10028533     \n"
    " 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n"
    " 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n"
    " 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n";
}
