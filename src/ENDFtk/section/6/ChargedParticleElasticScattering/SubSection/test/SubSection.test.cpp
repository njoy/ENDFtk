#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using SubSection = 
section::Type< 6 >::ChargedParticleElasticScattering::SubSection;
using LegendreCoefficients = 
section::Type< 6 >::ChargedParticleElasticScattering::LegendreCoefficients;
using NuclearAmplitudeExpansion = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearAmplitudeExpansion;
using NuclearPlusInterference = 
section::Type< 6 >::ChargedParticleElasticScattering::NuclearPlusInterference;

std::string chunkLTP1();
void verifyChunkLTP1( const SubSection& );
std::string chunkLTP2();
void verifyChunkLTP2( const SubSection& );
std::string chunkLTP12();
std::string chunkLTP14();
std::string chunkLTP15();
void verifyChunkLTP( int, const SubSection& );
std::string invalidLTP();

SCENARIO( "SubSection" ) {

  GIVEN( "valid data for a SubSection with LTP=1" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int nl = 3;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                       11, 12, 13, 14, 15 };

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection(
            NuclearAmplitudeExpansion( energy, nl, std::move( values ) ) );
        verifyChunkLTP1( subsection );
      } // THEN
    } // GIVEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkLTP1();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkLTP1( subsection );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a SubSection with LTP=2" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > values = { 1, 2, 3, 4 };

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection(
                       LegendreCoefficients( energy, std::move( values ) ) );
        verifyChunkLTP2( subsection );
      } // THEN
    } // GIVEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkLTP2();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkLTP2( subsection );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a SubSection with LTP=12" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int ltp = 12;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( NuclearPlusInterference( energy, ltp,
                                                        std::move( values ) ) );
        verifyChunkLTP( 12, subsection );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkLTP12();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkLTP( 12, subsection );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a SubSection with LTP=14" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int ltp = 14;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( NuclearPlusInterference( energy, ltp,
                                                        std::move( values ) ) );
        verifyChunkLTP( 14, subsection );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkLTP14();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkLTP( 14, subsection );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a SubSection with LTP=15" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      int ltp = 15;
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };
      std::vector< double > cosines = { 1, 3, 5 };
      std::vector< double > probabilities = { 2, 4, 6 };

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( NuclearPlusInterference( energy, ltp,
                                                        std::move( values ) ) );
        verifyChunkLTP( 15, subsection );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::string string = chunkLTP15();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "a SubSection can be constructed and members can be tested" ) {

        SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );
        verifyChunkLTP( 15, subsection );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a valid instance of SubSection with LTP=1" ) {

    std::string string = chunkLTP1();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection with LTP=2" ) {

    std::string string = chunkLTP2();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection with LTP=12" ) {

    std::string string = chunkLTP12();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection with LTP=14" ) {

    std::string string = chunkLTP14();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "a valid instance of SubSection with LTP=15" ) {

    std::string string = chunkLTP15();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    SubSection subsection( begin, end, lineNumber, 9228, 6, 5 );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      subsection.print( output, 9228, 6, 5 );
      REQUIRE( buffer == string );
    }
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "a string representation is used with an invalid LTP" ) {

      std::string string = invalidLTP();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown upon construction" ) {

        REQUIRE_THROWS( SubSection( begin, end, lineNumber, 9228, 6, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkLTP1() {
  return
    " 0.000000+0 1.000000-5          1          0         15          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n";
}

void verifyChunkLTP1( const SubSection& subsection ) {

  auto chunk =
  std::experimental::get< NuclearAmplitudeExpansion >( subsection.data() );
  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( 1 == chunk.LTP() );
  REQUIRE( 15 == chunk.NW() );
  REQUIRE( 3 == chunk.NL() );
  REQUIRE( 7 == chunk.scatteringCoefficients().size() );
  REQUIRE( 1. == Approx( chunk.scatteringCoefficients()[0] ) );
  REQUIRE( 2. == Approx( chunk.scatteringCoefficients()[1] ) );
  REQUIRE( 3. == Approx( chunk.scatteringCoefficients()[2] ) );
  REQUIRE( 4. == Approx( chunk.scatteringCoefficients()[3] ) );
  REQUIRE( 5. == Approx( chunk.scatteringCoefficients()[4] ) );
  REQUIRE( 6. == Approx( chunk.scatteringCoefficients()[5] ) );
  REQUIRE( 7. == Approx( chunk.scatteringCoefficients()[6] ) );
  REQUIRE( 4 == chunk.realInterferenceCoefficients().size() );
  REQUIRE( 8. == Approx( chunk.realInterferenceCoefficients()[0] ) );
  REQUIRE( 10. == Approx( chunk.realInterferenceCoefficients()[1] ) );
  REQUIRE( 12. == Approx( chunk.realInterferenceCoefficients()[2] ) );
  REQUIRE( 14. == Approx( chunk.realInterferenceCoefficients()[3] ) );
  REQUIRE( 4 == chunk.imaginaryInterferenceCoefficients().size() );
  REQUIRE( 9. == Approx( chunk.imaginaryInterferenceCoefficients()[0] ) );
  REQUIRE( 11. == Approx( chunk.imaginaryInterferenceCoefficients()[1] ) );
  REQUIRE( 13. == Approx( chunk.imaginaryInterferenceCoefficients()[2] ) );
  REQUIRE( 15. == Approx( chunk.imaginaryInterferenceCoefficients()[3] ) );

  REQUIRE( 1 == subsection.LTP() );
  REQUIRE( 1e-5 == Approx( subsection.energy() ) );
  REQUIRE( 15 == subsection.NW() );
  REQUIRE( 3 == subsection.NL() );
  REQUIRE( 4 == subsection.NC() );
}

std::string chunkLTP2() {
  return
    " 0.000000+0 1.000000-5          2          0          4          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n";
}

void verifyChunkLTP2( const SubSection& subsection ) {

  auto chunk =
  std::experimental::get< LegendreCoefficients >( subsection.data() );
  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( 2 == chunk.LTP() );
  REQUIRE( 4 == chunk.NW() );
  REQUIRE( 3 == chunk.NL() );
  REQUIRE( 4 == chunk.coefficients().size() );
  REQUIRE( 1. == Approx( chunk.coefficients()[0] ) );
  REQUIRE( 2. == Approx( chunk.coefficients()[1] ) );
  REQUIRE( 3. == Approx( chunk.coefficients()[2] ) );
  REQUIRE( 4. == Approx( chunk.coefficients()[3] ) );

  REQUIRE( 2 == subsection.LTP() );
  REQUIRE( 1e-5 == Approx( subsection.energy() ) );
  REQUIRE( 4 == subsection.NW() );
  REQUIRE( 3 == subsection.NL() );
  REQUIRE( 2 == subsection.NC() );
}
std::string chunkLTP12() {
  return
    " 0.000000+0 1.000000-5         12          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkLTP14() {
  return
    " 0.000000+0 1.000000-5         14          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

std::string chunkLTP15() {
  return
    " 0.000000+0 1.000000-5         15          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

void verifyChunkLTP( int ltp, const SubSection& subsection ) {

  auto chunk =
  std::experimental::get< NuclearPlusInterference >( subsection.data() );
  REQUIRE( 1e-5 == Approx( chunk.energy() ) );

  REQUIRE( ltp == chunk.LTP() );
  REQUIRE( 6 == chunk.NW() );
  REQUIRE( 3 == chunk.NL() );
  REQUIRE( 3 == chunk.cosines().size() );
  REQUIRE( 1. == Approx( chunk.cosines()[0] ) );
  REQUIRE( 3. == Approx( chunk.cosines()[1] ) );
  REQUIRE( 5. == Approx( chunk.cosines()[2] ) );
  REQUIRE( 3 == chunk.probabilities().size() );
  REQUIRE( 2. == Approx( chunk.probabilities()[0] ) );
  REQUIRE( 4. == Approx( chunk.probabilities()[1] ) );
  REQUIRE( 6. == Approx( chunk.probabilities()[2] ) );

  REQUIRE( ltp == subsection.LTP() );
  REQUIRE( 1e-5 == Approx( subsection.energy() ) );
  REQUIRE( 6 == subsection.NW() );
  REQUIRE( 3 == subsection.NL() );
  REQUIRE( 2 == subsection.NC() );
}

std::string invalidLTP() {
  return
    " 0.000000+0 1.000000-5          0          0          6          39228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

