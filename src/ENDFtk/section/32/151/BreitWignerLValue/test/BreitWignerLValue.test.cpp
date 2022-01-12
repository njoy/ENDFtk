#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using BreitWignerLValue =
section::Type< 32, 151 >::BreitWignerLValue;

std::string chunk();
void verifyChunk( const BreitWignerLValue& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "BreitWignerLValue" ) {

  GIVEN( "valid data for a BreitWignerLValue" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double l = 1.;
      std::vector< double > er = { -1.470000e+5, 4.730000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gt = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gf = { 3., 4. };
      std::vector< double > de2 = { 5., 6. };
      std::vector< double > dn2 = { 7., 8. };
      std::vector< double > dndg = { 9., 10. };
      std::vector< double > dg2 = { 11., 12. };
      std::vector< double > dndf = { 13., 14. };
      std::vector< double > dgdf = { 15., 16. };
      std::vector< double > df2 = { 17., 18. };
      std::vector< double > djdn = { 19., 20. };
      std::vector< double > djdg = { 21., 22. };
      std::vector< double > djdf = { 23., 24. };
      std::vector< double > dj2 = { 25., 26. };

      BreitWignerLValue chunk( awri, l,
                               std::move( er ), std::move( aj ),
                               std::move( gt ), std::move( gn ),
                               std::move( gg ), std::move( gf ),
                               std::move( de2 ), std::move( dn2 ),
                               std::move( dndg ), std::move( dg2 ),
                               std::move( dndf ), std::move( dgdf ),
                               std::move( df2 ), std::move( djdn ),
                               std::move( djdg ), std::move( djdf ),
                               std::move( dj2 ) );

      THEN( "a BreitWignerLValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      BreitWignerLValue chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a BreitWignerLValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 32, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the data is empty" ) {

      double awri = 1.982069e+1;
      double qx = 1.0;
      double l = 1.;
      bool lrx = true;
      std::vector< double > er = {};
      std::vector< double > aj = {};
      std::vector< double > gt = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gf = {};
      std::vector< double > de2 = {};
      std::vector< double > dn2 = {};
      std::vector< double > dndg = {};
      std::vector< double > dg2 = {};
      std::vector< double > dndf = {};
      std::vector< double > dgdf = {};
      std::vector< double > df2 = {};
      std::vector< double > djdn = {};
      std::vector< double > djdg = {};
      std::vector< double > djdf = {};
      std::vector< double > dj2 = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( BreitWignerLValue( awri, l,
                                         std::move( er ), std::move( aj ),
                                         std::move( gt ), std::move( gn ),
                                         std::move( gg ), std::move( gf ),
                                         std::move( de2 ), std::move( dn2 ),
                                         std::move( dndg ), std::move( dg2 ),
                                         std::move( dndf ), std::move( dgdf ),
                                         std::move( df2 ), std::move( djdn ),
                                         std::move( djdg ), std::move( djdf ),
                                         std::move( dj2 ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different sizes" ) {

      double awri = 1.982069e+1;
      double qx = 1.0;
      double l = 1.;
      bool lrx = true;
      std::vector< double > wrong = { -1.470000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gt = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gf = { 3., 4. };
      std::vector< double > de2 = { 5., 6. };
      std::vector< double > dn2 = { 7., 8. };
      std::vector< double > dndg = { 9., 10. };
      std::vector< double > dg2 = { 11., 12. };
      std::vector< double > dndf = { 13., 14. };
      std::vector< double > dgdf = { 15., 16. };
      std::vector< double > df2 = { 17., 18. };
      std::vector< double > djdn = { 19., 20. };
      std::vector< double > djdg = { 21., 22. };
      std::vector< double > djdf = { 23., 24. };
      std::vector< double > dj2 = { 25., 26. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( BreitWignerLValue( awri, l,
                                         std::move( wrong ), std::move( aj ),
                                         std::move( gt ), std::move( gn ),
                                         std::move( gg ), std::move( gf ),
                                         std::move( de2 ), std::move( dn2 ),
                                         std::move( dndg ), std::move( dg2 ),
                                         std::move( dndf ), std::move( dgdf ),
                                         std::move( df2 ), std::move( djdn ),
                                         std::move( djdg ), std::move( djdf ),
                                         std::move( dj2 ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( BreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( BreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = noNumberResonances();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( BreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.982069+1 0.000000+0          1          0         36          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n"
    " 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n"
    " 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1 0.000000+0102532151     \n";
}

void verifyChunk( const BreitWignerLValue& chunk ) {

  CHECK( 1.982069e+1 == Approx( chunk.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );

  CHECK( 2 == chunk.NRS() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.AJ().size() );
  CHECK( 2 == chunk.spinValues().size() );
  CHECK( 2 == chunk.GT().size() );
  CHECK( 2 == chunk.totalWidths().size() );
  CHECK( 2 == chunk.GN().size() );
  CHECK( 2 == chunk.neutronWidths().size() );
  CHECK( 2 == chunk.GG().size() );
  CHECK( 2 == chunk.gammaWidths().size() );
  CHECK( 2 == chunk.GF().size() );
  CHECK( 2 == chunk.fissionWidths().size() );
  CHECK( 2 == chunk.resonances().size() );

  CHECK( -1.470000e+5 == Approx( chunk.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[0] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[1] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[0] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[1] ) );
  CHECK( 5.470695e+2 == Approx( chunk.GT()[0] ) );
  CHECK( 1.072946e+5 == Approx( chunk.GT()[1] ) );
  CHECK( 5.470695e+2 == Approx( chunk.totalWidths()[0] ) );
  CHECK( 1.072946e+5 == Approx( chunk.totalWidths()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.GN()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.GN()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.neutronWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.neutronWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.GG()[0] ) );
  CHECK( 0.56 == Approx( chunk.GG()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.gammaWidths()[0] ) );
  CHECK( 0.56 == Approx( chunk.gammaWidths()[1] ) );
  CHECK( 3. == Approx( chunk.GF()[0] ) );
  CHECK( 4. == Approx( chunk.GF()[1] ) );
  CHECK( 3. == Approx( chunk.fissionWidths()[0] ) );
  CHECK( 4. == Approx( chunk.fissionWidths()[1] ) );

  CHECK( 5. == Approx( chunk.DE2()[0] ) );
  CHECK( 6. == Approx( chunk.DE2()[1] ) );
  CHECK( 5. == Approx( chunk.resonanceEnergyVariances()[0] ) );
  CHECK( 6. == Approx( chunk.resonanceEnergyVariances()[1] ) );
  CHECK( 25. == Approx( chunk.DJ2()[0] ) );
  CHECK( 26. == Approx( chunk.DJ2()[1] ) );
  CHECK( 25. == Approx( chunk.spinVariances()[0] ) );
  CHECK( 26. == Approx( chunk.spinVariances()[1] ) );
  CHECK( 7. == Approx( chunk.DN2()[0] ) );
  CHECK( 8. == Approx( chunk.DN2()[1] ) );
  CHECK( 7. == Approx( chunk.neutronWidthVariances()[0] ) );
  CHECK( 8. == Approx( chunk.neutronWidthVariances()[1] ) );
  CHECK( 11. == Approx( chunk.DG2()[0] ) );
  CHECK( 12. == Approx( chunk.DG2()[1] ) );
  CHECK( 11. == Approx( chunk.gammaWidthVariances()[0] ) );
  CHECK( 12. == Approx( chunk.gammaWidthVariances()[1] ) );
  CHECK( 17. == Approx( chunk.DF2()[0] ) );
  CHECK( 18. == Approx( chunk.DF2()[1] ) );
  CHECK( 17. == Approx( chunk.fissionWidthVariances()[0] ) );
  CHECK( 18. == Approx( chunk.fissionWidthVariances()[1] ) );
  CHECK( 19. == Approx( chunk.DJDN()[0] ) );
  CHECK( 20. == Approx( chunk.DJDN()[1] ) );
  CHECK( 19. == Approx( chunk.spinAndNeutronWidthCovariances()[0] ) );
  CHECK( 20. == Approx( chunk.spinAndNeutronWidthCovariances()[1] ) );
  CHECK( 21. == Approx( chunk.DJDG()[0] ) );
  CHECK( 22. == Approx( chunk.DJDG()[1] ) );
  CHECK( 21. == Approx( chunk.spinAndGammaWidthCovariances()[0] ) );
  CHECK( 22. == Approx( chunk.spinAndGammaWidthCovariances()[1] ) );
  CHECK( 23. == Approx( chunk.DJDF()[0] ) );
  CHECK( 24. == Approx( chunk.DJDF()[1] ) );
  CHECK( 23. == Approx( chunk.spinAndFissionWidthCovariances()[0] ) );
  CHECK( 24. == Approx( chunk.spinAndFissionWidthCovariances()[1] ) );
  CHECK(  9. == Approx( chunk.DNDG()[0] ) );
  CHECK( 10. == Approx( chunk.DNDG()[1] ) );
  CHECK(  9. == Approx( chunk.neutronAndGammaWidthCovariances()[0] ) );
  CHECK( 10. == Approx( chunk.neutronAndGammaWidthCovariances()[1] ) );
  CHECK( 13. == Approx( chunk.DNDF()[0] ) );
  CHECK( 14. == Approx( chunk.DNDF()[1] ) );
  CHECK( 13. == Approx( chunk.neutronAndFissionWidthCovariances()[0] ) );
  CHECK( 14. == Approx( chunk.neutronAndFissionWidthCovariances()[1] ) );
  CHECK( 15. == Approx( chunk.DGDF()[0] ) );
  CHECK( 16. == Approx( chunk.DGDF()[1] ) );
  CHECK( 15. == Approx( chunk.gammaAndFissionWidthCovariances()[0] ) );
  CHECK( 16. == Approx( chunk.gammaAndFissionWidthCovariances()[1] ) );

  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].ER() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].ER() ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].resonanceEnergy() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].resonanceEnergy() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].spin() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].spin() ) );
  CHECK( 5.470695e+2 == Approx( chunk.resonances()[0].GT() ) );
  CHECK( 1.072946e+5 == Approx( chunk.resonances()[1].GT() ) );
  CHECK( 5.470695e+2 == Approx( chunk.resonances()[0].totalWidth() ) );
  CHECK( 1.072946e+5 == Approx( chunk.resonances()[1].totalWidth() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].GN() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].GN() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].neutronWidth() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].neutronWidth() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].GG() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].GG() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].gammaWidth() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].gammaWidth() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].GF() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].GF() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].fissionWidth() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].fissionWidth() ) );

  CHECK( 5. == Approx( chunk.resonances()[0].DE2() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].DE2() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].resonanceEnergyVariance() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].resonanceEnergyVariance() ) );
  CHECK( 25. == Approx( chunk.resonances()[0].DJ2() ) );
  CHECK( 26. == Approx( chunk.resonances()[1].DJ2() ) );
  CHECK( 25. == Approx( chunk.resonances()[0].spinVariance() ) );
  CHECK( 26. == Approx( chunk.resonances()[1].spinVariance() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].DN2() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].DN2() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].neutronWidthVariance() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].neutronWidthVariance() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].DG2() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].DG2() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].gammaWidthVariance() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].gammaWidthVariance() ) );
  CHECK( 17. == Approx( chunk.resonances()[0].DF2() ) );
  CHECK( 18. == Approx( chunk.resonances()[1].DF2() ) );
  CHECK( 17. == Approx( chunk.resonances()[0].fissionWidthVariance() ) );
  CHECK( 18. == Approx( chunk.resonances()[1].fissionWidthVariance() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].DE2() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].DE2() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].resonanceEnergyVariance() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].resonanceEnergyVariance() ) );
  CHECK( 25. == Approx( chunk.resonances()[0].DJ2() ) );
  CHECK( 26. == Approx( chunk.resonances()[1].DJ2() ) );
  CHECK( 25. == Approx( chunk.resonances()[0].spinVariance() ) );
  CHECK( 26. == Approx( chunk.resonances()[1].spinVariance() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].DN2() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].DN2() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].neutronWidthVariance() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].neutronWidthVariance() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].DG2() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].DG2() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].gammaWidthVariance() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].gammaWidthVariance() ) );
  CHECK( 17. == Approx( chunk.resonances()[0].DF2() ) );
  CHECK( 18. == Approx( chunk.resonances()[1].DF2() ) );
  CHECK( 17. == Approx( chunk.resonances()[0].fissionWidthVariance() ) );
  CHECK( 18. == Approx( chunk.resonances()[1].fissionWidthVariance() ) );
  CHECK( 19. == Approx( chunk.resonances()[0].DJDN() ) );
  CHECK( 20. == Approx( chunk.resonances()[1].DJDN() ) );
  CHECK( 19. == Approx( chunk.resonances()[0].spinAndNeutronWidthCovariance() ) );
  CHECK( 20. == Approx( chunk.resonances()[1].spinAndNeutronWidthCovariance() ) );
  CHECK( 21. == Approx( chunk.resonances()[0].DJDG() ) );
  CHECK( 22. == Approx( chunk.resonances()[1].DJDG() ) );
  CHECK( 21. == Approx( chunk.resonances()[0].spinAndGammaWidthCovariance() ) );
  CHECK( 22. == Approx( chunk.resonances()[1].spinAndGammaWidthCovariance() ) );
  CHECK( 23. == Approx( chunk.resonances()[0].DJDF() ) );
  CHECK( 24. == Approx( chunk.resonances()[1].DJDF() ) );
  CHECK( 23. == Approx( chunk.resonances()[0].spinAndFissionWidthCovariance() ) );
  CHECK( 24. == Approx( chunk.resonances()[1].spinAndFissionWidthCovariance() ) );
  CHECK(  9. == Approx( chunk.resonances()[0].DNDG() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].DNDG() ) );
  CHECK(  9. == Approx( chunk.resonances()[0].neutronAndGammaWidthCovariance() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].neutronAndGammaWidthCovariance() ) );
  CHECK( 13. == Approx( chunk.resonances()[0].DNDF() ) );
  CHECK( 14. == Approx( chunk.resonances()[1].DNDF() ) );
  CHECK( 13. == Approx( chunk.resonances()[0].neutronAndFissionWidthCovariance() ) );
  CHECK( 14. == Approx( chunk.resonances()[1].neutronAndFissionWidthCovariance() ) );
  CHECK( 15. == Approx( chunk.resonances()[0].DGDF() ) );
  CHECK( 16. == Approx( chunk.resonances()[1].DGDF() ) );
  CHECK( 15. == Approx( chunk.resonances()[0].gammaAndFissionWidthCovariance() ) );
  CHECK( 16. == Approx( chunk.resonances()[1].gammaAndFissionWidthCovariance() ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 0.000000+0          1          0         35          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n"
    " 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n"
    " 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1           102532151     \n";
}

std::string zeroSize() {
  return
    " 1.982069+1 0.000000+0          0          0          0          21025 2151     \n";
}

std::string noNumberResonances() {
  return
    " 1.982069+1 1.000000+0          1          1         36          01025 2151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n"
    " 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n"
    " 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1 0.000000+0102532151     \n";
}
