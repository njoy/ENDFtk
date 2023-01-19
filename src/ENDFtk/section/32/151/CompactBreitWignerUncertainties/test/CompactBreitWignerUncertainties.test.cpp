#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactBreitWignerUncertainties =
section::Type< 32, 151 >::CompactBreitWignerUncertainties;

std::string chunk();
void verifyChunk( const CompactBreitWignerUncertainties& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "CompactBreitWignerUncertainties" ) {

  GIVEN( "valid data for a CompactBreitWignerUncertainties" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double qx = 15.;
      bool lrx = true;
      std::vector< double > er = { -1.470000e+5, 4.730000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gt = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gf = { 3., 4. };
      std::vector< double > der = { 5., 6. };
      std::vector< double > dgn = { 7., 8. };
      std::vector< double > dgg = { 9., 10. };
      std::vector< double > dgf = { 11., 12. };

      CompactBreitWignerUncertainties chunk( awri, qx, lrx,
                                             std::move( er ), std::move( aj ),
                                             std::move( gt ), std::move( gn ),
                                             std::move( gg ), std::move( gf ),
                                             std::move( der ), std::move( dgn ),
                                             std::move( dgg ), std::move( dgf ) );

      THEN( "a CompactBreitWignerUncertainties can be constructed and members "
            "can be tested" ) {

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

      CompactBreitWignerUncertainties chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a CompactBreitWignerUncertainties can be constructed and members "
            "can be tested" ) {

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
      double qx = 15.;
      bool lrx = true;
      std::vector< double > er = {};
      std::vector< double > aj = {};
      std::vector< double > gt = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gf = {};
      std::vector< double > der = {};
      std::vector< double > dgn = {};
      std::vector< double > dgg = {};
      std::vector< double > dgf = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactBreitWignerUncertainties(
                          awri, qx, lrx,
                          std::move( er ), std::move( aj ),
                          std::move( gt ), std::move( gn ),
                          std::move( gg ), std::move( gf ),
                          std::move( der ), std::move( dgn ),
                          std::move( dgg ), std::move( dgf ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different sizes" ) {

      double awri = 1.982069e+1;
      double qx = 15.;
      bool lrx = true;
      std::vector< double > wrong = { -1.470000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gt = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gf = { 3., 4. };
      std::vector< double > der = { 5., 6. };
      std::vector< double > dgn = { 7., 8. };
      std::vector< double > dgg = { 9., 10. };
      std::vector< double > dgf = { 11., 12. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactBreitWignerUncertainties(
                          awri, qx, lrx,
                          std::move( wrong ), std::move( aj ),
                          std::move( gt ), std::move( gn ),
                          std::move( gg ), std::move( gf ),
                          std::move( der ), std::move( dgn ),
                          std::move( dgg ), std::move( dgf ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRSA is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactBreitWignerUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactBreitWignerUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = noNumberResonances();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactBreitWignerUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.982069+1 1.500000+1          0          1         24          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n";
}

void verifyChunk( const CompactBreitWignerUncertainties& chunk ) {

  CHECK( 1.982069e+1 == Approx( chunk.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 15. == Approx( chunk.QX() ) );
  CHECK( 15. == Approx( chunk.competitiveQValue() ) );
  CHECK( true == chunk.LRX() );
  CHECK( true == chunk.competitiveWidthFlag() );

  CHECK( 2 == chunk.NRSA() );
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
  CHECK( 2 == chunk.DER().size() );
  CHECK( 2 == chunk.resonanceEnergyUncertainties().size() );
  CHECK( 2 == chunk.DGN().size() );
  CHECK( 2 == chunk.neutronWidthUncertainties().size() );
  CHECK( 2 == chunk.DGG().size() );
  CHECK( 2 == chunk.gammaWidthUncertainties().size() );
  CHECK( 2 == chunk.DGF().size() );
  CHECK( 2 == chunk.fissionWidthUncertainties().size() );

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

  CHECK( 5. == Approx( chunk.DER()[0] ) );
  CHECK( 6. == Approx( chunk.DER()[1] ) );
  CHECK( 5. == Approx( chunk.resonanceEnergyUncertainties()[0] ) );
  CHECK( 6. == Approx( chunk.resonanceEnergyUncertainties()[1] ) );
  CHECK( 7. == Approx( chunk.DGN()[0] ) );
  CHECK( 8. == Approx( chunk.DGN()[1] ) );
  CHECK( 7. == Approx( chunk.neutronWidthUncertainties()[0] ) );
  CHECK( 8. == Approx( chunk.neutronWidthUncertainties()[1] ) );
  CHECK( 9. == Approx( chunk.DGG()[0] ) );
  CHECK( 10. == Approx( chunk.DGG()[1] ) );
  CHECK( 9. == Approx( chunk.gammaWidthUncertainties()[0] ) );
  CHECK( 10. == Approx( chunk.gammaWidthUncertainties()[1] ) );
  CHECK( 11. == Approx( chunk.DGF()[0] ) );
  CHECK( 12. == Approx( chunk.DGF()[1] ) );
  CHECK( 11. == Approx( chunk.fissionWidthUncertainties()[0] ) );
  CHECK( 12. == Approx( chunk.fissionWidthUncertainties()[1] ) );

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

  CHECK( 5. == Approx( chunk.resonances()[0].DER() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].DER() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].resonanceEnergyUncertainty() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].resonanceEnergyUncertainty() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].DGN() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].DGN() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].neutronWidthUncertainty() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].neutronWidthUncertainty() ) );
  CHECK( 9. == Approx( chunk.resonances()[0].DGG() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].DGG() ) );
  CHECK( 9. == Approx( chunk.resonances()[0].gammaWidthUncertainty() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].gammaWidthUncertainty() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].DGF() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].DGF() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].fissionWidthUncertainty() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].fissionWidthUncertainty() ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 1.500000+1          0          1         23          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n";
}

std::string zeroSize() {
  return
    " 1.982069+1 1.500000+1          0          1          0          0102532151     \n";
}

std::string noNumberResonances() {
  return
    " 1.982069+1 1.500000+1          0          1         24          0102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n";
}
