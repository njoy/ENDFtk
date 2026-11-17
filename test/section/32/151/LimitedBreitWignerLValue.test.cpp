// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/32.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LimitedBreitWignerLValue =
section::Type< 32, 151 >::LimitedBreitWignerLValue;

std::string chunk();
void verifyChunk( const LimitedBreitWignerLValue& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "LimitedBreitWignerLValue" ) {

  GIVEN( "valid data for a LimitedBreitWignerLValue" ) {

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

      LimitedBreitWignerLValue chunk( awri, l,
                                      std::move( er ), std::move( aj ),
                                      std::move( gt ), std::move( gn ),
                                      std::move( gg ), std::move( gf ),
                                      std::move( de2 ), std::move( dn2 ),
                                      std::move( dndg ), std::move( dg2 ),
                                      std::move( dndf ), std::move( dgdf ),
                                      std::move( df2 ), std::move( djdn ),
                                      std::move( djdg ), std::move( djdf ),
                                      std::move( dj2 ) );

      THEN( "a LimitedBreitWignerLValue can be constructed and members can be "
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

      LimitedBreitWignerLValue chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a LimitedBreitWignerLValue can be constructed and members can be "
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
      double l = 1.;
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

        CHECK_THROWS( LimitedBreitWignerLValue(
                          awri, l,
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
      double l = 1.;
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

        CHECK_THROWS( LimitedBreitWignerLValue(
                          awri, l,
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

        CHECK_THROWS( LimitedBreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LimitedBreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = noNumberResonances();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LimitedBreitWignerLValue( begin, end, lineNumber, 1025, 32, 151 ) );
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

void verifyChunk( const LimitedBreitWignerLValue& chunk ) {

  CHECK_THAT( 1.982069e+1, WithinRel( chunk.AWRI() ) );
  CHECK_THAT( 1.982069e+1, WithinRel( chunk.atomicWeightRatio() ) );
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
  CHECK( 2 == chunk.DE2().size() );
  CHECK( 2 == chunk.resonanceEnergyVariances().size() );
  CHECK( 2 == chunk.DJ2().size() );
  CHECK( 2 == chunk.spinVariances().size() );
  CHECK( 2 == chunk.DN2().size() );
  CHECK( 2 == chunk.neutronWidthVariances().size() );
  CHECK( 2 == chunk.DG2().size() );
  CHECK( 2 == chunk.gammaWidthVariances().size() );
  CHECK( 2 == chunk.DF2().size() );
  CHECK( 2 == chunk.fissionWidthVariances().size() );
  CHECK( 2 == chunk.DJDN().size() );
  CHECK( 2 == chunk.spinAndNeutronWidthCovariances().size() );
  CHECK( 2 == chunk.DJDG().size() );
  CHECK( 2 == chunk.spinAndGammaWidthCovariances().size() );
  CHECK( 2 == chunk.DJDF().size() );
  CHECK( 2 == chunk.spinAndFissionWidthCovariances().size() );
  CHECK( 2 == chunk.DNDG().size() );
  CHECK( 2 == chunk.neutronAndGammaWidthCovariances().size() );
  CHECK( 2 == chunk.DNDF().size() );
  CHECK( 2 == chunk.neutronAndFissionWidthCovariances().size() );
  CHECK( 2 == chunk.DGDF().size() );
  CHECK( 2 == chunk.gammaAndFissionWidthCovariances().size() );
  CHECK( 2 == chunk.resonances().size() );

  CHECK_THAT( -1.470000e+5, WithinRel( chunk.ER()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.ER()[1] ) );
  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonanceEnergies()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonanceEnergies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinValues()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.spinValues()[1] ) );
  CHECK_THAT( 5.470695e+2, WithinRel( chunk.GT()[0] ) );
  CHECK_THAT( 1.072946e+5, WithinRel( chunk.GT()[1] ) );
  CHECK_THAT( 5.470695e+2, WithinRel( chunk.totalWidths()[0] ) );
  CHECK_THAT( 1.072946e+5, WithinRel( chunk.totalWidths()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.GN()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.GN()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.neutronWidths()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.neutronWidths()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.GG()[0] ) );
  CHECK_THAT( 0.56, WithinRel( chunk.GG()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.gammaWidths()[0] ) );
  CHECK_THAT( 0.56, WithinRel( chunk.gammaWidths()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.GF()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.GF()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.fissionWidths()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.fissionWidths()[1] ) );

  CHECK_THAT( 5., WithinRel( chunk.DE2()[0] ) );
  CHECK_THAT( 6., WithinRel( chunk.DE2()[1] ) );
  CHECK_THAT( 5., WithinRel( chunk.resonanceEnergyVariances()[0] ) );
  CHECK_THAT( 6., WithinRel( chunk.resonanceEnergyVariances()[1] ) );
  CHECK_THAT( 25., WithinRel( chunk.DJ2()[0] ) );
  CHECK_THAT( 26., WithinRel( chunk.DJ2()[1] ) );
  CHECK_THAT( 25., WithinRel( chunk.spinVariances()[0] ) );
  CHECK_THAT( 26., WithinRel( chunk.spinVariances()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.DN2()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.DN2()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.neutronWidthVariances()[0] ) );
  CHECK_THAT( 8., WithinRel( chunk.neutronWidthVariances()[1] ) );
  CHECK_THAT( 11., WithinRel( chunk.DG2()[0] ) );
  CHECK_THAT( 12., WithinRel( chunk.DG2()[1] ) );
  CHECK_THAT( 11., WithinRel( chunk.gammaWidthVariances()[0] ) );
  CHECK_THAT( 12., WithinRel( chunk.gammaWidthVariances()[1] ) );
  CHECK_THAT( 17., WithinRel( chunk.DF2()[0] ) );
  CHECK_THAT( 18., WithinRel( chunk.DF2()[1] ) );
  CHECK_THAT( 17., WithinRel( chunk.fissionWidthVariances()[0] ) );
  CHECK_THAT( 18., WithinRel( chunk.fissionWidthVariances()[1] ) );
  CHECK_THAT( 19., WithinRel( chunk.DJDN()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.DJDN()[1] ) );
  CHECK_THAT( 19., WithinRel( chunk.spinAndNeutronWidthCovariances()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.spinAndNeutronWidthCovariances()[1] ) );
  CHECK_THAT( 21., WithinRel( chunk.DJDG()[0] ) );
  CHECK_THAT( 22., WithinRel( chunk.DJDG()[1] ) );
  CHECK_THAT( 21., WithinRel( chunk.spinAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 22., WithinRel( chunk.spinAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 23., WithinRel( chunk.DJDF()[0] ) );
  CHECK_THAT( 24., WithinRel( chunk.DJDF()[1] ) );
  CHECK_THAT( 23., WithinRel( chunk.spinAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 24., WithinRel( chunk.spinAndFissionWidthCovariances()[1] ) );
  CHECK_THAT(  9., WithinRel( chunk.DNDG()[0] ) );
  CHECK_THAT( 10., WithinRel( chunk.DNDG()[1] ) );
  CHECK_THAT(  9., WithinRel( chunk.neutronAndGammaWidthCovariances()[0] ) );
  CHECK_THAT( 10., WithinRel( chunk.neutronAndGammaWidthCovariances()[1] ) );
  CHECK_THAT( 13., WithinRel( chunk.DNDF()[0] ) );
  CHECK_THAT( 14., WithinRel( chunk.DNDF()[1] ) );
  CHECK_THAT( 13., WithinRel( chunk.neutronAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 14., WithinRel( chunk.neutronAndFissionWidthCovariances()[1] ) );
  CHECK_THAT( 15., WithinRel( chunk.DGDF()[0] ) );
  CHECK_THAT( 16., WithinRel( chunk.DGDF()[1] ) );
  CHECK_THAT( 15., WithinRel( chunk.gammaAndFissionWidthCovariances()[0] ) );
  CHECK_THAT( 16., WithinRel( chunk.gammaAndFissionWidthCovariances()[1] ) );

  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonances()[0].ER() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonances()[1].ER() ) );
  CHECK_THAT( -1.470000e+5, WithinRel( chunk.resonances()[0].resonanceEnergy() ) );
  CHECK_THAT(  4.730000e+5, WithinRel( chunk.resonances()[1].resonanceEnergy() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[0].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[1].AJ() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[0].spin() ) );
  CHECK_THAT( 0.5, WithinRel( chunk.resonances()[1].spin() ) );
  CHECK_THAT( 5.470695e+2, WithinRel( chunk.resonances()[0].GT() ) );
  CHECK_THAT( 1.072946e+5, WithinRel( chunk.resonances()[1].GT() ) );
  CHECK_THAT( 5.470695e+2, WithinRel( chunk.resonances()[0].totalWidth() ) );
  CHECK_THAT( 1.072946e+5, WithinRel( chunk.resonances()[1].totalWidth() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.resonances()[0].GN() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.resonances()[1].GN() ) );
  CHECK_THAT( 3.680695e+2, WithinRel( chunk.resonances()[0].neutronWidth() ) );
  CHECK_THAT( 1.072900e+5, WithinRel( chunk.resonances()[1].neutronWidth() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.resonances()[0].GG() ) );
  CHECK_THAT( 0.56, WithinRel( chunk.resonances()[1].GG() ) );
  CHECK_THAT( 1.750000e+2, WithinRel( chunk.resonances()[0].gammaWidth() ) );
  CHECK_THAT( 0.56, WithinRel( chunk.resonances()[1].gammaWidth() ) );
  CHECK_THAT( 3., WithinRel( chunk.resonances()[0].GF() ) );
  CHECK_THAT( 4., WithinRel( chunk.resonances()[1].GF() ) );
  CHECK_THAT( 3., WithinRel( chunk.resonances()[0].fissionWidth() ) );
  CHECK_THAT( 4., WithinRel( chunk.resonances()[1].fissionWidth() ) );

  CHECK_THAT( 5., WithinRel( chunk.resonances()[0].DE2() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonances()[1].DE2() ) );
  CHECK_THAT( 5., WithinRel( chunk.resonances()[0].resonanceEnergyVariance() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonances()[1].resonanceEnergyVariance() ) );
  CHECK_THAT( 25., WithinRel( chunk.resonances()[0].DJ2() ) );
  CHECK_THAT( 26., WithinRel( chunk.resonances()[1].DJ2() ) );
  CHECK_THAT( 25., WithinRel( chunk.resonances()[0].spinVariance() ) );
  CHECK_THAT( 26., WithinRel( chunk.resonances()[1].spinVariance() ) );
  CHECK_THAT( 7., WithinRel( chunk.resonances()[0].DN2() ) );
  CHECK_THAT( 8., WithinRel( chunk.resonances()[1].DN2() ) );
  CHECK_THAT( 7., WithinRel( chunk.resonances()[0].neutronWidthVariance() ) );
  CHECK_THAT( 8., WithinRel( chunk.resonances()[1].neutronWidthVariance() ) );
  CHECK_THAT( 11., WithinRel( chunk.resonances()[0].DG2() ) );
  CHECK_THAT( 12., WithinRel( chunk.resonances()[1].DG2() ) );
  CHECK_THAT( 11., WithinRel( chunk.resonances()[0].gammaWidthVariance() ) );
  CHECK_THAT( 12., WithinRel( chunk.resonances()[1].gammaWidthVariance() ) );
  CHECK_THAT( 17., WithinRel( chunk.resonances()[0].DF2() ) );
  CHECK_THAT( 18., WithinRel( chunk.resonances()[1].DF2() ) );
  CHECK_THAT( 17., WithinRel( chunk.resonances()[0].fissionWidthVariance() ) );
  CHECK_THAT( 18., WithinRel( chunk.resonances()[1].fissionWidthVariance() ) );
  CHECK_THAT( 5., WithinRel( chunk.resonances()[0].DE2() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonances()[1].DE2() ) );
  CHECK_THAT( 5., WithinRel( chunk.resonances()[0].resonanceEnergyVariance() ) );
  CHECK_THAT( 6., WithinRel( chunk.resonances()[1].resonanceEnergyVariance() ) );
  CHECK_THAT( 25., WithinRel( chunk.resonances()[0].DJ2() ) );
  CHECK_THAT( 26., WithinRel( chunk.resonances()[1].DJ2() ) );
  CHECK_THAT( 25., WithinRel( chunk.resonances()[0].spinVariance() ) );
  CHECK_THAT( 26., WithinRel( chunk.resonances()[1].spinVariance() ) );
  CHECK_THAT( 7., WithinRel( chunk.resonances()[0].DN2() ) );
  CHECK_THAT( 8., WithinRel( chunk.resonances()[1].DN2() ) );
  CHECK_THAT( 7., WithinRel( chunk.resonances()[0].neutronWidthVariance() ) );
  CHECK_THAT( 8., WithinRel( chunk.resonances()[1].neutronWidthVariance() ) );
  CHECK_THAT( 11., WithinRel( chunk.resonances()[0].DG2() ) );
  CHECK_THAT( 12., WithinRel( chunk.resonances()[1].DG2() ) );
  CHECK_THAT( 11., WithinRel( chunk.resonances()[0].gammaWidthVariance() ) );
  CHECK_THAT( 12., WithinRel( chunk.resonances()[1].gammaWidthVariance() ) );
  CHECK_THAT( 17., WithinRel( chunk.resonances()[0].DF2() ) );
  CHECK_THAT( 18., WithinRel( chunk.resonances()[1].DF2() ) );
  CHECK_THAT( 17., WithinRel( chunk.resonances()[0].fissionWidthVariance() ) );
  CHECK_THAT( 18., WithinRel( chunk.resonances()[1].fissionWidthVariance() ) );
  CHECK_THAT( 19., WithinRel( chunk.resonances()[0].DJDN() ) );
  CHECK_THAT( 20., WithinRel( chunk.resonances()[1].DJDN() ) );
  CHECK_THAT( 19., WithinRel( chunk.resonances()[0].spinAndNeutronWidthCovariance() ) );
  CHECK_THAT( 20., WithinRel( chunk.resonances()[1].spinAndNeutronWidthCovariance() ) );
  CHECK_THAT( 21., WithinRel( chunk.resonances()[0].DJDG() ) );
  CHECK_THAT( 22., WithinRel( chunk.resonances()[1].DJDG() ) );
  CHECK_THAT( 21., WithinRel( chunk.resonances()[0].spinAndGammaWidthCovariance() ) );
  CHECK_THAT( 22., WithinRel( chunk.resonances()[1].spinAndGammaWidthCovariance() ) );
  CHECK_THAT( 23., WithinRel( chunk.resonances()[0].DJDF() ) );
  CHECK_THAT( 24., WithinRel( chunk.resonances()[1].DJDF() ) );
  CHECK_THAT( 23., WithinRel( chunk.resonances()[0].spinAndFissionWidthCovariance() ) );
  CHECK_THAT( 24., WithinRel( chunk.resonances()[1].spinAndFissionWidthCovariance() ) );
  CHECK_THAT(  9., WithinRel( chunk.resonances()[0].DNDG() ) );
  CHECK_THAT( 10., WithinRel( chunk.resonances()[1].DNDG() ) );
  CHECK_THAT(  9., WithinRel( chunk.resonances()[0].neutronAndGammaWidthCovariance() ) );
  CHECK_THAT( 10., WithinRel( chunk.resonances()[1].neutronAndGammaWidthCovariance() ) );
  CHECK_THAT( 13., WithinRel( chunk.resonances()[0].DNDF() ) );
  CHECK_THAT( 14., WithinRel( chunk.resonances()[1].DNDF() ) );
  CHECK_THAT( 13., WithinRel( chunk.resonances()[0].neutronAndFissionWidthCovariance() ) );
  CHECK_THAT( 14., WithinRel( chunk.resonances()[1].neutronAndFissionWidthCovariance() ) );
  CHECK_THAT( 15., WithinRel( chunk.resonances()[0].DGDF() ) );
  CHECK_THAT( 16., WithinRel( chunk.resonances()[1].DGDF() ) );
  CHECK_THAT( 15., WithinRel( chunk.resonances()[0].gammaAndFissionWidthCovariance() ) );
  CHECK_THAT( 16., WithinRel( chunk.resonances()[1].gammaAndFissionWidthCovariance() ) );

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
