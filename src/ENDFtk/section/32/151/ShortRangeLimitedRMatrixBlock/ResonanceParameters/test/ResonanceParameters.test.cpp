#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ResonanceParameters =
section::Type< 32, 151 >::ShortRangeLimitedRMatrixBlock::ResonanceParameters;

std::string chunk();
void verifyChunk( const ResonanceParameters& );
std::string invalidSize();
std::string zeroSize();
std::string zeroNX();

SCENARIO( "ResonanceParameters" ) {

  GIVEN( "valid data for a ResonanceParameters" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { -1.223300e+6, 7.788000e+3 };
      std::vector< std::vector< double > > parameters =
        { { 1., 9.611086e+5, 2., 3., 4., 5. },
          { 1.455, 1.187354e+3, 6., 7., 8., 9. } };

      ResonanceParameters chunk( std::move( energies ),
                                 std::move( parameters ) );

      THEN( "a ResonanceParameters can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ResonanceParameters chunk( begin, end, lineNumber, 2625, 2, 151 );

      THEN( "a ResonanceParameters can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      std::vector< double > energies = { -1.223300e+6, 7.788000e+3 };
      std::vector< std::vector< double > > wrong =
        { { 1., 9.611086e+5, 2., 3., 4., 5. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different number of channels" ) {

      std::vector< double > energies = { -1.223300e+6, 7.788000e+3 };
      std::vector< std::vector< double > > parameters =
        { { 1., 9.611086e+5, 2., 3., 4., 5. },
          { 1.455, 1.187354e+3, 6., 7., 8. } }; // one less width for energy 2

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( parameters ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is empty" ) {

      std::vector< double > energies = {};
      std::vector< std::vector< double > > parameters = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( parameters ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NCH is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( begin, end, lineNumber,
                                           2625, 2, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL is used" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( begin, end, lineNumber,
                                           2625, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          6          2         24          42625 2151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 2.000000+0 3.000000+0 4.000000+02625 2151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 6.000000+0 7.000000+0 8.000000+02625 2151     \n"
    " 9.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n";
}

void verifyChunk( const ResonanceParameters& chunk ) {

  CHECK( 6 == chunk.NCH() );
  CHECK( 6 == chunk.numberChannels() );
  CHECK( 2 == chunk.NRB() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 4 == chunk.NX() );
  CHECK( 4 == chunk.numberLines() );

  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.GAM().size() );
  CHECK( 2 == chunk.resonanceParameters().size() );

  CHECK( -1.223300e+6 == Approx( chunk.ER()[0] ) );
  CHECK(  7.788000e+3 == Approx( chunk.ER()[1] ) );
  CHECK( -1.223300e+6 == Approx( chunk.resonanceEnergies()[0] ) );
  CHECK(  7.788000e+3 == Approx( chunk.resonanceEnergies()[1] ) );
  CHECK( 6 == chunk.GAM()[0].size() );
  CHECK( 6 == chunk.GAM()[1].size() );
  CHECK( 1. == Approx( chunk.GAM()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( chunk.GAM()[0][1] ) );
  CHECK( 2. == Approx( chunk.GAM()[0][2] ) );
  CHECK( 3. == Approx( chunk.GAM()[0][3] ) );
  CHECK( 4. == Approx( chunk.GAM()[0][4] ) );
  CHECK( 5. == Approx( chunk.GAM()[0][5] ) );
  CHECK( 1.455 == Approx( chunk.GAM()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( chunk.GAM()[1][1] ) );
  CHECK( 6. == Approx( chunk.GAM()[1][2] ) );
  CHECK( 7. == Approx( chunk.GAM()[1][3] ) );
  CHECK( 8. == Approx( chunk.GAM()[1][4] ) );
  CHECK( 9. == Approx( chunk.GAM()[1][5] ) );
  CHECK( 6 == chunk.resonanceParameters()[0].size() );
  CHECK( 6 == chunk.resonanceParameters()[1].size() );
  CHECK( 1. == Approx( chunk.resonanceParameters()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( chunk.resonanceParameters()[0][1] ) );
  CHECK( 2. == Approx( chunk.resonanceParameters()[0][2] ) );
  CHECK( 3. == Approx( chunk.resonanceParameters()[0][3] ) );
  CHECK( 4. == Approx( chunk.resonanceParameters()[0][4] ) );
  CHECK( 5. == Approx( chunk.resonanceParameters()[0][5] ) );
  CHECK( 1.455 == Approx( chunk.resonanceParameters()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( chunk.resonanceParameters()[1][1] ) );
  CHECK( 6. == Approx( chunk.resonanceParameters()[1][2] ) );
  CHECK( 7. == Approx( chunk.resonanceParameters()[1][3] ) );
  CHECK( 8. == Approx( chunk.resonanceParameters()[1][4] ) );
  CHECK( 9. == Approx( chunk.resonanceParameters()[1][5] ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 0.000000+0          0          2         23          42625 2151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 1.000000+0 2.000000+0 3.000000+02625 2151     \n"
    " 4.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 5.000000+0 6.000000+0 7.000000+02625 2151     \n"
    " 8.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0           2625 2151     \n";
}

std::string zeroSize() {
  return
    " 0.000000+0 0.000000+0          0          2          0          42625 2151     \n";
}
