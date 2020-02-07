#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using AverageDecayEnergies = section::Type< 8, 457 >::AverageDecayEnergies;
using DiscreteSpectrum = section::Type< 8, 457 >::DiscreteSpectrum;
using ContinuousSpectrum = section::Type< 8, 457 >::ContinuousSpectrum;
using DecaySpectrum = section::Type< 8, 457 >::DecaySpectrum;
using DecayModes = section::Type< 8, 457 >::DecayModes;
using DecayMode = section::Type< 8, 457 >::DecayMode;

// macros don't like multiple template arguments
using section8457 = section::Type< 8, 457 >;

std::string chunkForRadioactiveNuclideWithSpectra();
void verifyChunkForRadioactiveNuclideWithSpectra(
          const section::Type< 8,457 >& );
std::string chunkForRadioactiveNuclideWithoutSpectra();
void verifyChunkForRadioactiveNuclideWithoutSpectra(
          const section::Type< 8,457 >& );
std::string chunkForStableNuclide();
void verifyChunkForStableNuclide( const section::Type< 8,457 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 8, 457 >" ) {

  GIVEN( "valid data for a section::Type< 8, 457 > for a radioactive nuclide "
         "with spectra" ) {

    std::string sectionString = chunkForRadioactiveNuclideWithSpectra() + 
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      double zaid = 9.524200e+4;
      double awr = 2.399801e+2;
      int lis = 2;
      int liso = 1;
      double spin = 5.;
      double parity = -1.;

      AverageDecayEnergies energies( {{ 4.449622e+9, 6.311520e+7 }}, 
                                     { {{ 4.008322e+4, 4.128931e+3 }},
                                       {{ 5.373671e+3, 3.660206e+2 }},
                                       {{ 2.441003e+4, 6.191754e+2 }} } );

      DecayModes modes( 5., -1.,
           { { 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 },
             { 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 },
             { 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 } } );

      std::vector< DecaySpectrum > spectra =
        { { 0.0, {{ 1., 0. }}, {{ 2.107044e+2, 1.576284e+1 }},
            { { 3., {{ 4.863000e+4, 5.000000e+1 }},
                {{ 1.420112e-6, 2.85306e-10 }}, 0.0,
              {{ 0.0, 0.0 }}, {{ 7.010000e+5, 1.106180e-2 }}, {{ 0.0, 0.0 }},
              {{ 3.315735e+5, 5.608008e+3 }} },
            { 4., {{ 4.935000e+4, 2.000000e+1 }},
              {{ 1.335690e-3, 5.409179e-5 }}, 0.0,
              {{ 0.0, 0.0 }}, {{ 8.209999e-1, 0.000000e+0 }}, {{ 0.0, 0.0 }},
              {{ 6.160000e-1, 8.999999e-3 }} } } },
          { 1.0, {{ 0.5, 0.25 }}, {{ 3.107044e+2, 4.576284e+1 }},
            { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
              { 6.133200e-7, 6.133300e-7, 6.02040e-17 } } } };

      section::Type< 8, 457 > chunk( zaid, awr, lis, liso,
                                     std::move( energies ),
                                     std::move( modes ),
                                     std::move( spectra ) );

      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForRadioactiveNuclideWithSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );

      section::Type< 8, 457 > chunk( head, begin, end, lineNumber, 3580 );
      
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForRadioactiveNuclideWithSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string >
        section( head, begin, position, end, lineNumber );

      section::Type< 8, 457 > chunk = section.parse< 8, 457 >( lineNumber );
      
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForRadioactiveNuclideWithSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 8, 457 > for a radioactive nuclide "
         "without spectra" ) {

    std::string sectionString = chunkForRadioactiveNuclideWithoutSpectra() + 
                                validSEND();

    WHEN( "the data is given explicitly" ) {

      double zaid = 9.524200e+4;
      double awr = 2.399801e+2;
      int lis = 2;
      int liso = 1;
      double spin = 5.;
      double parity = -1.;

      AverageDecayEnergies energies( {{ 4.449622e+9, 6.311520e+7 }}, 
                                     { {{ 4.008322e+4, 4.128931e+3 }},
                                       {{ 5.373671e+3, 3.660206e+2 }},
                                       {{ 2.441003e+4, 6.191754e+2 }} } );
  
      DecayModes modes( 5., -1.,
           { { 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 },
             { 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 },
             { 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 } } );

      section::Type< 8, 457 > chunk( zaid, awr, lis, liso,
                                     std::move( energies ),
                                     std::move( modes ), {} );
  
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested for a radioactive nuclide without spectra" ) {

        verifyChunkForRadioactiveNuclideWithoutSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );

      section::Type< 8, 457 > chunk( head, begin, end, lineNumber, 3580 );
      
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForRadioactiveNuclideWithoutSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ) {

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string >
        section( head, begin, position, end, lineNumber );

      section::Type< 8, 457 > chunk = section.parse< 8, 457 >( lineNumber );
      
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForRadioactiveNuclideWithoutSpectra( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a section::Type< 8, 457 > for a stable nuclide" ) {

    std::string sectionString = chunkForStableNuclide() + validSEND();

    WHEN( "the data is given explicitly" ) {

      double zaid = 9.524200e+4;
      double awr = 2.399801e+2;
      int lis = 2;
      int liso = 1;
      double spin = 5.;
      double parity = -1.;

      section::Type< 8, 457 > chunk( zaid, awr, lis, liso, spin, parity );

      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested for a stable nuclide" ) {

        verifyChunkForStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1; 
      HeadRecord head( begin, end, lineNumber );
      
      section::Type< 8, 457 > chunk( head, begin, end, lineNumber, 3580 );

      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } //WHEN

    WHEN( "there is a syntaxTree::Section" ) {

      std::string sectionString = chunkForStableNuclide() + validSEND();
      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 1;
      auto head = HEAD( position, end, lineNumber );
      syntaxTree::Section< std::string >
        section( head, begin, position, end, lineNumber );

      section::Type< 8, 457 > chunk = section.parse< 8, 457 >( lineNumber );
      
      THEN( "a section::Type< 8, 457 > can be constructed and members can be "
            "tested" ) {

        verifyChunkForStableNuclide( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3580, 8 );

        REQUIRE( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 8, 457 >" ) {

    WHEN( "a string representation of a valid section::Type< 8, 457 > for a "
          "radioactive nuclide with spectra with an invalid SEND" ) {

      std::string sectionString = chunkForRadioactiveNuclideWithSpectra() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section8457( head, begin, end, lineNumber, 3580 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 8, 457 > for a "
          "radioactive nuclide without spectra with an invalid SEND" ) {

      std::string sectionString = chunkForRadioactiveNuclideWithoutSpectra() +
                                  invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section8457( head, begin, end, lineNumber, 3580 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation of a valid section::Type< 8, 457 > for a "
          "stable nuclide with an invalid SEND" ) {

      std::string sectionString = chunkForStableNuclide() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );
      
      THEN( "an exception is thrown" ) {

        REQUIRE_THROWS( section8457( head, begin, end, lineNumber, 3580 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkForRadioactiveNuclideWithSpectra() {
  return
    " 9.524200+4 2.399801+2          2          1          0          23580 8457     \n"
    " 4.449622+9 6.311520+7          0          0          6          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n"
    " 5.000000+0-1.000000+0          0          0         18          33580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n"
    " 0.000000+0 0.000000+0          0          0          6          23580 8457     \n"
    " 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n"
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n"
    " 4.935000+4 2.000000+1          0          0         12          03580 8457     \n"
    " 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n"
    " 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n"
    " 0.000000+0 1.000000+0          1          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 3.107044+2 4.576284+1 5.000000-1 2.500000-13580 8457     \n"
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n";
}

void verifyChunkForRadioactiveNuclideWithSpectra(
        const section::Type< 8,457 >& chunk ) {

  REQUIRE( 457 == chunk.MT() );
  REQUIRE( 457 == chunk.sectionNumber() );

  REQUIRE( 9.524200e+4 == Approx( chunk.ZA() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 2 == chunk.LIS() );
  REQUIRE( 2 == chunk.excitedState() );
  REQUIRE( 1 == chunk.LISO() );
  REQUIRE( 1 == chunk.isomericState() );
  REQUIRE( false == chunk.NST() );
  REQUIRE( false == chunk.isStable() );
  REQUIRE( 5.0 == Approx( chunk.spin() ) );
  REQUIRE( -1. == Approx( chunk.parity() ) );
  auto halfLife = chunk.halfLife();
  REQUIRE( 4.449622e+9 == Approx( halfLife[0] ) );
  REQUIRE( 6.311520e+7 == Approx( halfLife[1] ) );

  auto averageEnergies = chunk.averageDecayEnergies();
  auto halfLife2 = averageEnergies.halfLife();
  REQUIRE( 4.449622e+9 == Approx( halfLife2[0] ) );
  REQUIRE( 6.311520e+7 == Approx( halfLife2[1] ) );
  REQUIRE( 3 == averageEnergies.numberDecayEnergies() );
  REQUIRE( 3 == averageEnergies.decayEnergies().size() );
  auto lightParticle = averageEnergies.decayEnergies()[0];
  REQUIRE( 4.008322e+4 == Approx( lightParticle[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle[1] ) );
  auto electroMagnetic = averageEnergies.decayEnergies()[1];
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic[1] ) );
  auto heavyParticle = averageEnergies.decayEnergies()[2];
  REQUIRE( 2.441003e+4 == Approx( heavyParticle[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle[1] ) );

  auto lightParticle2 = averageEnergies.lightParticleDecayEnergy();
  REQUIRE( 4.008322e+4 == Approx( lightParticle2[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle2[1] ) );
  auto electroMagnetic2 = averageEnergies.electromagneticDecayEnergy();
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic2[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic2[1] ) );
  auto heavyParticle2 = averageEnergies.heavyParticleDecayEnergy();
  REQUIRE( 2.441003e+4 == Approx( heavyParticle2[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle2[1] ) );

  auto decayModes = chunk.decayModes();
  REQUIRE( 5.0 == Approx( decayModes.SPI() ) );
  REQUIRE( 5.0 == Approx( decayModes.spin() ) );
  REQUIRE( -1. == Approx( decayModes.PAR() ) );
  REQUIRE( -1. == Approx( decayModes.parity() ) );

  auto data = decayModes.decayModes();
  REQUIRE( 3 == decayModes.NDK() );
  REQUIRE( 3 == decayModes.numberDecayModes() );
  REQUIRE( 3 == data.size() );
  REQUIRE( 4. == Approx( data[0].RTYP() ) );
  REQUIRE( 4. == Approx( data[0].decayChain() ) );
  REQUIRE( 0. == Approx( data[0].RFS() ) );
  REQUIRE( 0. == Approx( data[0].finalIsomericState() ) );
  REQUIRE( 5.637120e+6 == Approx( data[0].Q()[0] ) );
  REQUIRE( 2.549510e+2 == Approx( data[0].Q()[1] ) );
  REQUIRE( 5.637120e+6 == Approx( data[0].qValue()[0] ) );
  REQUIRE( 2.549510e+2 == Approx( data[0].qValue()[1] ) );
  REQUIRE( 4.590000e-3 == Approx( data[0].BR()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[0].BR()[1] ) );
  REQUIRE( 4.590000e-3 == Approx( data[0].branchingRatio()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[0].branchingRatio()[1] ) );
  REQUIRE( 3. == Approx( data[1].RTYP() ) );
  REQUIRE( 3. == Approx( data[1].decayChain() ) );
  REQUIRE( 0. == Approx( data[1].RFS() ) );
  REQUIRE( 0. == Approx( data[1].finalIsomericState() ) );
  REQUIRE( 4.860000e+4 == Approx( data[1].Q()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( data[1].Q()[1] ) );
  REQUIRE( 4.860000e+4 == Approx( data[1].qValue()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( data[1].qValue()[1] ) );
  REQUIRE( 9.954100e-1 == Approx( data[1].BR()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[1].BR()[1] ) );
  REQUIRE( 9.954100e-1 == Approx( data[1].branchingRatio()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[1].branchingRatio()[1] ) );
  REQUIRE( 6. == Approx( data[2].RTYP() ) );
  REQUIRE( 6. == Approx( data[2].decayChain() ) );
  REQUIRE( 0. == Approx( data[2].RFS() ) );
  REQUIRE( 0. == Approx( data[2].finalIsomericState() ) );
  REQUIRE( 1.884000e+8 == Approx( data[2].Q()[0] ) );
  REQUIRE( 3.700000e+6 == Approx( data[2].Q()[1] ) );
  REQUIRE( 1.884000e+8 == Approx( data[2].qValue()[0] ) );
  REQUIRE( 3.700000e+6 == Approx( data[2].qValue()[1] ) );
  REQUIRE( 1.60000e-10 == Approx( data[2].BR()[0] ) );
  REQUIRE( 6.00000e-11 == Approx( data[2].BR()[1] ) );
  REQUIRE( 1.60000e-10 == Approx( data[2].branchingRatio()[0] ) );
  REQUIRE( 6.00000e-11 == Approx( data[2].branchingRatio()[1] ) );

  REQUIRE( 2 == chunk.NSP() );
  REQUIRE( 2 == chunk.numberDecaySpectra() );
  REQUIRE( 2 == chunk.decaySpectra().size() );

  auto spectrum1 = chunk.decaySpectra()[0];
  REQUIRE( 0. == spectrum1.STYP() );
  REQUIRE( 0. == spectrum1.radiationType() );

  REQUIRE( 0 == spectrum1.LCON() );
  REQUIRE( 0 == spectrum1.continuumSpectrumFlag() );
  REQUIRE( 0 == spectrum1.LCOV() );
  REQUIRE( 0 == spectrum1.covarianceFlag() );
  REQUIRE( 2 == spectrum1.NER() );
  REQUIRE( 2 == spectrum1.numberDiscreteSpectra() );

  REQUIRE( 1. == Approx( spectrum1.FD()[0] ) );
  REQUIRE( 0. == Approx( spectrum1.FD()[1] ) );
  REQUIRE( 1. == Approx( spectrum1.discreteNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( spectrum1.discreteNormalisationFactor()[1] ) );
  REQUIRE( 0. == Approx( spectrum1.FC()[0] ) );
  REQUIRE( 0. == Approx( spectrum1.FC()[1] ) );
  REQUIRE( 0. == Approx( spectrum1.continuousNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( spectrum1.continuousNormalisationFactor()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( spectrum1.ERAV()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( spectrum1.ERAV()[1] ) );
  REQUIRE( 2.107044e+2 == Approx( spectrum1.averageDecayEnergy()[0] ) );
  REQUIRE( 1.576284e+1 == Approx( spectrum1.averageDecayEnergy()[1] ) );

  REQUIRE( std::nullopt == spectrum1.continuousSpectrum() );

  auto discrete = spectrum1.discreteSpectra();
  REQUIRE( 3. == discrete[0].RTYP() );
  REQUIRE( 3. == discrete[0].decayChain() );
  REQUIRE( 12 == discrete[0].NT() );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].ER()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].ER()[1] ) );
  REQUIRE( 4.863000e+4 == Approx( discrete[0].discreteEnergy()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( discrete[0].discreteEnergy()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].RI()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].RI()[1] ) );
  REQUIRE( 1.420112e-6 == Approx( discrete[0].relativeIntensity()[0] ) );
  REQUIRE( 2.85306e-10 == Approx( discrete[0].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[0].TYPE() );
  REQUIRE( 0. == discrete[0].type() );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].RICC()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].RICC()[1] ) );
  REQUIRE( 7.010000e+5 == Approx( discrete[0].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 1.106180e-2 == Approx( discrete[0].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[0].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].RICL()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].RICL()[1] ) );
  REQUIRE( 3.315735e+5 == Approx( discrete[0].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 5.608008e+3 == Approx( discrete[0].internalConversionCoefficientLShell()[1] ) );
  REQUIRE( 4. == discrete[1].decayChain() );
  REQUIRE( 12 == discrete[1].NT() );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].ER()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].ER()[1] ) );
  REQUIRE( 4.935000e+4 == Approx( discrete[1].discreteEnergy()[0] ) );
  REQUIRE( 2.000000e+1 == Approx( discrete[1].discreteEnergy()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].RI()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].RI()[1] ) );
  REQUIRE( 1.335690e-3 == Approx( discrete[1].relativeIntensity()[0] ) );
  REQUIRE( 5.409179e-5 == Approx( discrete[1].relativeIntensity()[1] ) );
  REQUIRE( 0. == discrete[1].TYPE() );
  REQUIRE( 0. == discrete[1].type() );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RIS()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalPairFormationCoefficient()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].RICC()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].RICC()[1] ) );
  REQUIRE( 8.209999e-1 == Approx( discrete[1].totalInternalConversionCoefficient()[0] ) );
  REQUIRE( 0.000000e+0 == Approx( discrete[1].totalInternalConversionCoefficient()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].RICK()[1] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[0] ) );
  REQUIRE( 0.0 == Approx( discrete[1].internalConversionCoefficientKShell()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].RICL()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].RICL()[1] ) );
  REQUIRE( 6.160000e-1 == Approx( discrete[1].internalConversionCoefficientLShell()[0] ) );
  REQUIRE( 8.999999e-3 == Approx( discrete[1].internalConversionCoefficientLShell()[1] ) );

  auto spectrum2 = chunk.decaySpectra()[1];
  REQUIRE( 1. == spectrum2.STYP() );
  REQUIRE( 1. == spectrum2.radiationType() );

  REQUIRE( 1 == spectrum2.LCON() );
  REQUIRE( 1 == spectrum2.continuumSpectrumFlag() );
  REQUIRE( 0 == spectrum2.LCOV() );
  REQUIRE( 0 == spectrum2.covarianceFlag() );
  REQUIRE( 0 == spectrum2.NER() );
  REQUIRE( 0 == spectrum2.numberDiscreteSpectra() );

  REQUIRE( 0. == Approx( spectrum2.FD()[0] ) );
  REQUIRE( 0. == Approx( spectrum2.FD()[1] ) );
  REQUIRE( 0. == Approx( spectrum2.discreteNormalisationFactor()[0] ) );
  REQUIRE( 0. == Approx( spectrum2.discreteNormalisationFactor()[1] ) );
  REQUIRE( 0.5 == Approx( spectrum2.FC()[0] ) );
  REQUIRE( 0.25 == Approx( spectrum2.FC()[1] ) );
  REQUIRE( 0.5 == Approx( spectrum2.continuousNormalisationFactor()[0] ) );
  REQUIRE( 0.25 == Approx( spectrum2.continuousNormalisationFactor()[1] ) );
  REQUIRE( 3.107044e+2 == Approx( spectrum2.ERAV()[0] ) );
  REQUIRE( 4.576284e+1 == Approx( spectrum2.ERAV()[1] ) );
  REQUIRE( 3.107044e+2 == Approx( spectrum2.averageDecayEnergy()[0] ) );
  REQUIRE( 4.576284e+1 == Approx( spectrum2.averageDecayEnergy()[1] ) );

  REQUIRE( std::nullopt != spectrum2.continuousSpectrum() );

  ContinuousSpectrum continuous = *( spectrum2.continuousSpectrum() );
  REQUIRE( 4. == continuous.RTYP() );
  REQUIRE( 4. == continuous.decayChain() );
  REQUIRE( 3 == continuous.NP() );
  REQUIRE( 1 == continuous.NR() );
  REQUIRE( 1 == continuous.interpolants().size() );
  REQUIRE( 1 == continuous.boundaries().size() );
  REQUIRE( 1 == continuous.interpolants()[0] );
  REQUIRE( 3 == continuous.boundaries()[0] );
  REQUIRE( 3 == continuous.energies().size() );
  REQUIRE( 3 == continuous.spectralValues().size() );
  REQUIRE( 0.0 == Approx( continuous.energies()[0] ) );
  REQUIRE( 5e+5 == Approx( continuous.energies()[1] ) );
  REQUIRE( 7.3e+6 == Approx( continuous.energies()[2] ) );
  REQUIRE( 6.133200e-7 == Approx( continuous.spectralValues()[0] ) );
  REQUIRE( 6.133300e-7 == Approx( continuous.spectralValues()[1] ) );
  REQUIRE( 6.02040e-17 == Approx( continuous.spectralValues()[2] ) );

  REQUIRE( 20 == chunk.NC() );
}

std::string chunkForRadioactiveNuclideWithoutSpectra() {
  return
    " 9.524200+4 2.399801+2          2          1          0          03580 8457     \n"
    " 4.449622+9 6.311520+7          0          0          6          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n"
    " 5.000000+0-1.000000+0          0          0         18          33580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n";
}

void verifyChunkForRadioactiveNuclideWithoutSpectra(
        const section::Type< 8,457 >& chunk ) {

  REQUIRE( 457 == chunk.MT() );
  REQUIRE( 457 == chunk.sectionNumber() );

  REQUIRE( 9.524200e+4 == Approx( chunk.ZA() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 2 == chunk.LIS() );
  REQUIRE( 2 == chunk.excitedState() );
  REQUIRE( 1 == chunk.LISO() );
  REQUIRE( 1 == chunk.isomericState() );
  REQUIRE( false == chunk.NST() );
  REQUIRE( false == chunk.isStable() );
  REQUIRE( 5.0 == Approx( chunk.SPI() ) );
  REQUIRE( 5.0 == Approx( chunk.spin() ) );
  REQUIRE( -1. == Approx( chunk.PAR() ) );
  REQUIRE( -1. == Approx( chunk.parity() ) );
  auto halfLife = chunk.halfLife();
  REQUIRE( 4.449622e+9 == Approx( halfLife[0] ) );
  REQUIRE( 6.311520e+7 == Approx( halfLife[1] ) );

  auto averageEnergies = chunk.averageDecayEnergies();
  auto halfLife2 = averageEnergies.halfLife();
  REQUIRE( 4.449622e+9 == Approx( halfLife2[0] ) );
  REQUIRE( 6.311520e+7 == Approx( halfLife2[1] ) );
  REQUIRE( 3 == averageEnergies.numberDecayEnergies() );
  REQUIRE( 3 == averageEnergies.decayEnergies().size() );
  auto lightParticle = averageEnergies.decayEnergies()[0];
  REQUIRE( 4.008322e+4 == Approx( lightParticle[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle[1] ) );
  auto electroMagnetic = averageEnergies.decayEnergies()[1];
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic[1] ) );
  auto heavyParticle = averageEnergies.decayEnergies()[2];
  REQUIRE( 2.441003e+4 == Approx( heavyParticle[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle[1] ) );

  auto lightParticle2 = averageEnergies.lightParticleDecayEnergy();
  REQUIRE( 4.008322e+4 == Approx( lightParticle2[0] ) );
  REQUIRE( 4.128931e+3 == Approx( lightParticle2[1] ) );
  auto electroMagnetic2 = averageEnergies.electromagneticDecayEnergy();
  REQUIRE( 5.373671e+3 == Approx( electroMagnetic2[0] ) );
  REQUIRE( 3.660206e+2 == Approx( electroMagnetic2[1] ) );
  auto heavyParticle2 = averageEnergies.heavyParticleDecayEnergy();
  REQUIRE( 2.441003e+4 == Approx( heavyParticle2[0] ) );
  REQUIRE( 6.191754e+2 == Approx( heavyParticle2[1] ) );

  auto decayModes = chunk.decayModes();
  REQUIRE( 5.0 == Approx( decayModes.SPI() ) );
  REQUIRE( 5.0 == Approx( decayModes.spin() ) );
  REQUIRE( -1. == Approx( decayModes.PAR() ) );
  REQUIRE( -1. == Approx( decayModes.parity() ) );

  auto data = decayModes.decayModes();
  REQUIRE( 3 == decayModes.NDK() );
  REQUIRE( 3 == data.size() );
  REQUIRE( 4. == Approx( data[0].RTYP() ) );
  REQUIRE( 4. == Approx( data[0].decayChain() ) );
  REQUIRE( 0. == Approx( data[0].RFS() ) );
  REQUIRE( 0. == Approx( data[0].finalIsomericState() ) );
  REQUIRE( 5.637120e+6 == Approx( data[0].Q()[0] ) );
  REQUIRE( 2.549510e+2 == Approx( data[0].Q()[1] ) );
  REQUIRE( 5.637120e+6 == Approx( data[0].qValue()[0] ) );
  REQUIRE( 2.549510e+2 == Approx( data[0].qValue()[1] ) );
  REQUIRE( 4.590000e-3 == Approx( data[0].BR()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[0].BR()[1] ) );
  REQUIRE( 4.590000e-3 == Approx( data[0].branchingRatio()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[0].branchingRatio()[1] ) );
  REQUIRE( 3. == Approx( data[1].RTYP() ) );
  REQUIRE( 3. == Approx( data[1].decayChain() ) );
  REQUIRE( 0. == Approx( data[1].RFS() ) );
  REQUIRE( 0. == Approx( data[1].finalIsomericState() ) );
  REQUIRE( 4.860000e+4 == Approx( data[1].Q()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( data[1].Q()[1] ) );
  REQUIRE( 4.860000e+4 == Approx( data[1].qValue()[0] ) );
  REQUIRE( 5.000000e+1 == Approx( data[1].qValue()[1] ) );
  REQUIRE( 9.954100e-1 == Approx( data[1].BR()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[1].BR()[1] ) );
  REQUIRE( 9.954100e-1 == Approx( data[1].branchingRatio()[0] ) );
  REQUIRE( 1.200000e-4 == Approx( data[1].branchingRatio()[1] ) );
  REQUIRE( 6. == Approx( data[2].RTYP() ) );
  REQUIRE( 6. == Approx( data[2].decayChain() ) );
  REQUIRE( 0. == Approx( data[2].RFS() ) );
  REQUIRE( 0. == Approx( data[2].finalIsomericState() ) );
  REQUIRE( 1.884000e+8 == Approx( data[2].Q()[0] ) );
  REQUIRE( 3.700000e+6 == Approx( data[2].Q()[1] ) );
  REQUIRE( 1.884000e+8 == Approx( data[2].qValue()[0] ) );
  REQUIRE( 3.700000e+6 == Approx( data[2].qValue()[1] ) );
  REQUIRE( 1.60000e-10 == Approx( data[2].BR()[0] ) );
  REQUIRE( 6.00000e-11 == Approx( data[2].BR()[1] ) );
  REQUIRE( 1.60000e-10 == Approx( data[2].branchingRatio()[0] ) );
  REQUIRE( 6.00000e-11 == Approx( data[2].branchingRatio()[1] ) );

  REQUIRE( 0 == chunk.NSP() );
  REQUIRE( 0 == chunk.numberDecaySpectra() );
  REQUIRE( 0 == chunk.decaySpectra().size() );

  REQUIRE( 7 == chunk.NC() );
}

std::string chunkForStableNuclide() {
  return
    " 9.524200+4 2.399801+2          2          1          1          03580 8457     \n"
    " 0.000000+0 0.000000+0          0          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n"
    " 5.000000+0-1.000000+0          0          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n";
}

void verifyChunkForStableNuclide( const section::Type< 8,457 >& chunk ) {

  REQUIRE( 457 == chunk.MT() );
  REQUIRE( 457 == chunk.sectionNumber() );

  REQUIRE( 9.524200e+4 == Approx( chunk.ZA() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.AWR() ) );
  REQUIRE( 2.399801e+2 == Approx( chunk.atomicWeightRatio() ) );
  REQUIRE( 2 == chunk.LIS() );
  REQUIRE( 2 == chunk.excitedState() );
  REQUIRE( 1 == chunk.LISO() );
  REQUIRE( 1 == chunk.isomericState() );
  REQUIRE( true == chunk.NST() );
  REQUIRE( true == chunk.isStable() );
  REQUIRE( 5.0 == Approx( chunk.SPI() ) );
  REQUIRE( 5.0 == Approx( chunk.spin() ) );
  REQUIRE( -1. == Approx( chunk.PAR() ) );
  REQUIRE( -1. == Approx( chunk.parity() ) );
  auto halfLife = chunk.halfLife();
  REQUIRE( 0.0 == Approx( halfLife[0] ) );
  REQUIRE( 0.0 == Approx( halfLife[1] ) );

  auto averageEnergies = chunk.averageDecayEnergies();
  auto halfLife1 = averageEnergies.halfLife();
  REQUIRE( 0.0 == Approx( halfLife1[0] ) );
  REQUIRE( 0.0 == Approx( halfLife1[1] ) );
  REQUIRE( 3 == averageEnergies.numberDecayEnergies() );
  REQUIRE( 3 == averageEnergies.decayEnergies().size() );
  auto lightParticle = averageEnergies.decayEnergies()[0];
  REQUIRE( 0.0 == Approx( lightParticle[0] ) );
  REQUIRE( 0.0 == Approx( lightParticle[1] ) );
  auto electroMagnetic = averageEnergies.decayEnergies()[1];
  REQUIRE( 0.0 == Approx( electroMagnetic[0] ) );
  REQUIRE( 0.0 == Approx( electroMagnetic[1] ) );
  auto heavyParticle = averageEnergies.decayEnergies()[2];
  REQUIRE( 0.0 == Approx( heavyParticle[0] ) );
  REQUIRE( 0.0 == Approx( heavyParticle[1] ) );
  auto lightParticle2 = averageEnergies.lightParticleDecayEnergy();
  REQUIRE( 0.0 == Approx( lightParticle2[0] ) );
  REQUIRE( 0.0 == Approx( lightParticle2[1] ) );
  auto electroMagnetic2 = averageEnergies.electromagneticDecayEnergy();
  REQUIRE( 0.0 == Approx( electroMagnetic2[0] ) );
  REQUIRE( 0.0 == Approx( electroMagnetic2[1] ) );
  auto heavyParticle2 = averageEnergies.heavyParticleDecayEnergy();
  REQUIRE( 0.0 == Approx( heavyParticle2[0] ) );
  REQUIRE( 0.0 == Approx( heavyParticle2[1] ) );

  auto decayModes = chunk.decayModes();

  REQUIRE( 5.0 == Approx( decayModes.SPI() ) );
  REQUIRE( 5.0 == Approx( decayModes.spin() ) );
  REQUIRE( -1. == Approx( decayModes.PAR() ) );
  REQUIRE( -1. == Approx( decayModes.parity() ) );
      
  auto data = decayModes.decayModes();
  REQUIRE( 0 == decayModes.NDK() );
  REQUIRE( 0 == decayModes.numberDecayModes() );
  REQUIRE( 1 == data.size() );
  REQUIRE( 0. == Approx( data[0].RTYP() ) );
  REQUIRE( 0. == Approx( data[0].decayChain() ) );
  REQUIRE( 0. == Approx( data[0].RFS() ) );
  REQUIRE( 0. == Approx( data[0].finalIsomericState() ) );
  REQUIRE( 0. == Approx( data[0].Q()[0] ) );
  REQUIRE( 0. == Approx( data[0].Q()[1] ) );
  REQUIRE( 0. == Approx( data[0].qValue()[0] ) );
  REQUIRE( 0. == Approx( data[0].qValue()[1] ) );
  REQUIRE( 0. == Approx( data[0].BR()[0] ) );
  REQUIRE( 0. == Approx( data[0].BR()[1] ) );
  REQUIRE( 0. == Approx( data[0].branchingRatio()[0] ) );
  REQUIRE( 0. == Approx( data[0].branchingRatio()[1] ) );

  REQUIRE( 0 == chunk.NSP() );
  REQUIRE( 0 == chunk.numberDecaySpectra() );
  REQUIRE( 0 == chunk.decaySpectra().size() );

  REQUIRE( 5 == chunk.NC() );
}

std::string validSEND() {
  return
    "                                                                  3580 8  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                  3580 8  4     \n";
}
