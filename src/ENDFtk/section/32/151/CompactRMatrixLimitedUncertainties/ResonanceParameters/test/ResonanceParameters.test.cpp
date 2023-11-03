#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ResonanceParameters =
section::Type< 32, 151 >::CompactRMatrixLimitedUncertainties::ResonanceParameters;

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
      std::vector< double > denergies = { 10., 12. };
      std::vector< std::vector< double > > dparameters =
        { { 13., 14., 15., 16., 17., 18. },
          { 19., 20., 21., 22., 23., 24. } };

      ResonanceParameters chunk( std::move( energies ),
                                 std::move( parameters ),
                                 std::move( denergies ),
                                 std::move( dparameters ) );

      THEN( "a ResonanceParameters can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ResonanceParameters chunk( begin, end, lineNumber, 2625, 32, 151 );

      THEN( "a ResonanceParameters can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 2625, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data has different sizes" ) {

      std::vector< double > energies = { -1.223300e+6, 7.788000e+3 };
      std::vector< std::vector< double > > wrong =
        { { 1., 9.611086e+5, 2., 3., 4., 5. } };
      std::vector< double > denergies = { 10., 12. };
      std::vector< std::vector< double > > dparameters =
        { { 13., 14., 15., 16., 17., 18. },
          { 19., 20., 21., 22., 23., 24. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( wrong ),
                                           std::move( denergies ),
                                           std::move( dparameters ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different number of channels" ) {

      std::vector< double > energies = { -1.223300e+6, 7.788000e+3 };
      std::vector< std::vector< double > > parameters =
        { { 1., 9.611086e+5, 2., 3., 4., 5. },
          { 1.455, 1.187354e+3, 6., 7., 8. } }; // one less width for energy 2
      std::vector< double > denergies = { 10., 12. };
      std::vector< std::vector< double > > dparameters =
        { { 13., 14., 15., 16., 17., 18. },
          { 19., 20., 21., 22., 23., 24. } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( parameters ),
                                           std::move( denergies ),
                                           std::move( dparameters ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is empty" ) {

      std::vector< double > energies = {};
      std::vector< std::vector< double > > parameters = {};
      std::vector< double > denergies = {};
      std::vector< std::vector< double > > dparameters = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( std::move( energies ),
                                           std::move( parameters ),
                                           std::move( denergies ),
                                           std::move( dparameters ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NCH is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( begin, end, lineNumber,
                                           2625, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL is used" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceParameters( begin, end, lineNumber,
                                           2625, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          2         48          4262532151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 2.000000+0 3.000000+0 4.000000+0262532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 1.000000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1262532151     \n"
    " 1.800000+1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 6.000000+0 7.000000+0 8.000000+0262532151     \n"
    " 9.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 1.200000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1262532151     \n"
    " 2.400000+1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n";
}

void verifyChunk( const ResonanceParameters& chunk ) {

  CHECK( 2 == chunk.NRSA() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 4 == chunk.NX() );
  CHECK( 4 == chunk.numberLines() );

  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.GAM().size() );
  CHECK( 2 == chunk.resonanceParameters().size() );
  CHECK( 2 == chunk.DER().size() );
  CHECK( 2 == chunk.resonanceEnergyUncertainties().size() );
  CHECK( 2 == chunk.DGAM().size() );
  CHECK( 2 == chunk.resonanceParameterUncertainties().size() );

  CHECK( -1.223300e+6 == Approx( chunk.ER()[0] ) );
  CHECK(  7.788000e+3 == Approx( chunk.ER()[1] ) );
  CHECK( -1.223300e+6 == Approx( chunk.resonanceEnergies()[0] ) );
  CHECK(  7.788000e+3 == Approx( chunk.resonanceEnergies()[1] ) );
  CHECK( 11 == chunk.GAM()[0].size() );
  CHECK( 11 == chunk.GAM()[1].size() );
  CHECK( 1. == Approx( chunk.GAM()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( chunk.GAM()[0][1] ) );
  CHECK( 2. == Approx( chunk.GAM()[0][2] ) );
  CHECK( 3. == Approx( chunk.GAM()[0][3] ) );
  CHECK( 4. == Approx( chunk.GAM()[0][4] ) );
  CHECK( 5. == Approx( chunk.GAM()[0][5] ) );
  CHECK( 0. == Approx( chunk.GAM()[0][6] ) );
  CHECK( 0. == Approx( chunk.GAM()[0][7] ) );
  CHECK( 0. == Approx( chunk.GAM()[0][8] ) );
  CHECK( 0. == Approx( chunk.GAM()[0][9] ) );
  CHECK( 0. == Approx( chunk.GAM()[0][10] ) );
  CHECK( 1.455 == Approx( chunk.GAM()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( chunk.GAM()[1][1] ) );
  CHECK( 6. == Approx( chunk.GAM()[1][2] ) );
  CHECK( 7. == Approx( chunk.GAM()[1][3] ) );
  CHECK( 8. == Approx( chunk.GAM()[1][4] ) );
  CHECK( 9. == Approx( chunk.GAM()[1][5] ) );
  CHECK( 0. == Approx( chunk.GAM()[1][6] ) );
  CHECK( 0. == Approx( chunk.GAM()[1][7] ) );
  CHECK( 0. == Approx( chunk.GAM()[1][8] ) );
  CHECK( 0. == Approx( chunk.GAM()[1][9] ) );
  CHECK( 0. == Approx( chunk.GAM()[1][10] ) );
  CHECK( 11 == chunk.resonanceParameters()[0].size() );
  CHECK( 11 == chunk.resonanceParameters()[1].size() );
  CHECK( 1. == Approx( chunk.resonanceParameters()[0][0] ) );
  CHECK( 9.611086e+5 == Approx( chunk.resonanceParameters()[0][1] ) );
  CHECK( 2. == Approx( chunk.resonanceParameters()[0][2] ) );
  CHECK( 3. == Approx( chunk.resonanceParameters()[0][3] ) );
  CHECK( 4. == Approx( chunk.resonanceParameters()[0][4] ) );
  CHECK( 5. == Approx( chunk.resonanceParameters()[0][5] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[0][6] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[0][7] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[0][8] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[0][9] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[0][10] ) );
  CHECK( 1.455 == Approx( chunk.resonanceParameters()[1][0] ) );
  CHECK( 1.187354e+3 == Approx( chunk.resonanceParameters()[1][1] ) );
  CHECK( 6. == Approx( chunk.resonanceParameters()[1][2] ) );
  CHECK( 7. == Approx( chunk.resonanceParameters()[1][3] ) );
  CHECK( 8. == Approx( chunk.resonanceParameters()[1][4] ) );
  CHECK( 9. == Approx( chunk.resonanceParameters()[1][5] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[1][6] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[1][7] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[1][8] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[1][9] ) );
  CHECK( 0. == Approx( chunk.resonanceParameters()[1][10] ) );

  CHECK( 10. == Approx( chunk.DER()[0] ) );
  CHECK( 12. == Approx( chunk.DER()[1] ) );
  CHECK( 10. == Approx( chunk.resonanceEnergyUncertainties()[0] ) );
  CHECK( 12. == Approx( chunk.resonanceEnergyUncertainties()[1] ) );
  CHECK( 11 == chunk.DGAM()[0].size() );
  CHECK( 11 == chunk.DGAM()[1].size() );
  CHECK( 13. == Approx( chunk.DGAM()[0][0] ) );
  CHECK( 14. == Approx( chunk.DGAM()[0][1] ) );
  CHECK( 15. == Approx( chunk.DGAM()[0][2] ) );
  CHECK( 16. == Approx( chunk.DGAM()[0][3] ) );
  CHECK( 17. == Approx( chunk.DGAM()[0][4] ) );
  CHECK( 18. == Approx( chunk.DGAM()[0][5] ) );
  CHECK( 0. == Approx( chunk.DGAM()[0][6] ) );
  CHECK( 0. == Approx( chunk.DGAM()[0][7] ) );
  CHECK( 0. == Approx( chunk.DGAM()[0][8] ) );
  CHECK( 0. == Approx( chunk.DGAM()[0][9] ) );
  CHECK( 0. == Approx( chunk.DGAM()[0][10] ) );
  CHECK( 19. == Approx( chunk.DGAM()[1][0] ) );
  CHECK( 20. == Approx( chunk.DGAM()[1][1] ) );
  CHECK( 21. == Approx( chunk.DGAM()[1][2] ) );
  CHECK( 22. == Approx( chunk.DGAM()[1][3] ) );
  CHECK( 23. == Approx( chunk.DGAM()[1][4] ) );
  CHECK( 24. == Approx( chunk.DGAM()[1][5] ) );
  CHECK( 0. == Approx( chunk.DGAM()[1][6] ) );
  CHECK( 0. == Approx( chunk.DGAM()[1][7] ) );
  CHECK( 0. == Approx( chunk.DGAM()[1][8] ) );
  CHECK( 0. == Approx( chunk.DGAM()[1][9] ) );
  CHECK( 0. == Approx( chunk.DGAM()[1][10] ) );
  CHECK( 11 == chunk.resonanceParameterUncertainties()[0].size() );
  CHECK( 11 == chunk.resonanceParameterUncertainties()[1].size() );
  CHECK( 13. == Approx( chunk.resonanceParameterUncertainties()[0][0] ) );
  CHECK( 14. == Approx( chunk.resonanceParameterUncertainties()[0][1] ) );
  CHECK( 15. == Approx( chunk.resonanceParameterUncertainties()[0][2] ) );
  CHECK( 16. == Approx( chunk.resonanceParameterUncertainties()[0][3] ) );
  CHECK( 17. == Approx( chunk.resonanceParameterUncertainties()[0][4] ) );
  CHECK( 18. == Approx( chunk.resonanceParameterUncertainties()[0][5] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[0][6] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[0][7] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[0][8] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[0][9] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[0][10] ) );
  CHECK( 19. == Approx( chunk.resonanceParameterUncertainties()[1][0] ) );
  CHECK( 20. == Approx( chunk.resonanceParameterUncertainties()[1][1] ) );
  CHECK( 21. == Approx( chunk.resonanceParameterUncertainties()[1][2] ) );
  CHECK( 22. == Approx( chunk.resonanceParameterUncertainties()[1][3] ) );
  CHECK( 23. == Approx( chunk.resonanceParameterUncertainties()[1][4] ) );
  CHECK( 24. == Approx( chunk.resonanceParameterUncertainties()[1][5] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[1][6] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[1][7] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[1][8] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[1][9] ) );
  CHECK( 0. == Approx( chunk.resonanceParameterUncertainties()[1][10] ) );

  CHECK( 9 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 0.000000+0 0.000000+0          0          2         47          4262532151     \n"
    "-1.223300+6 1.000000+0 9.611086+5 2.000000+0 3.000000+0 4.000000+0262532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 1.000000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1262532151     \n"
    " 1.800000+1 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 7.788000+3 1.455000+0 1.187354+3 6.000000+0 7.000000+0 8.000000+0262532151     \n"
    " 9.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n"
    " 1.200000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1262532151     \n"
    " 2.400000+1 0.000000+0 0.000000+0 0.000000+0 0.000000+0           262532151     \n";
}

std::string zeroSize() {
  return
    " 0.000000+0 0.000000+0          0          2          0          4262532151     \n";
}
