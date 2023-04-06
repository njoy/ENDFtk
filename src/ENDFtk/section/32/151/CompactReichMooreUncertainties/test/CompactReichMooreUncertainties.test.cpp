#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using CompactReichMooreUncertainties =
section::Type< 32, 151 >::CompactReichMooreUncertainties;

std::string chunk();
void verifyChunk( const CompactReichMooreUncertainties& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "CompactReichMooreUncertainties" ) {

  GIVEN( "valid data for a CompactReichMooreUncertainties" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      double apl = 15.;
      std::vector< double > er = { -1.470000e+5, 4.730000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gfa = { 3., 4. };
      std::vector< double > gfb = { 5., 6. };
      std::vector< double > der = { 7., 8. };
      std::vector< double > dgn = { 9., 10. };
      std::vector< double > dgg = { 11., 12. };
      std::vector< double > dgfa = { 13., 14. };
      std::vector< double > dgfb = { 15., 16. };

      CompactReichMooreUncertainties chunk( awri, apl,
                                            std::move( er ), std::move( aj ),
                                            std::move( gn ), std::move( gg ),
                                            std::move( gfa ), std::move( gfb ),
                                            std::move( der ), std::move( dgn ),
                                            std::move( dgg ), std::move( dgfa ),
                                            std::move( dgfb ) );

      THEN( "a CompactReichMooreUncertainties can be constructed and members "
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

      CompactReichMooreUncertainties chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a CompactReichMooreUncertainties can be constructed and members "
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
      double apl = 15.;
      std::vector< double > er = {};
      std::vector< double > aj = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gfa = {};
      std::vector< double > gfb = {};
      std::vector< double > der = {};
      std::vector< double > dgn = {};
      std::vector< double > dgg = {};
      std::vector< double > dgfa = {};
      std::vector< double > dgfb = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactReichMooreUncertainties(
                          awri, apl,
                          std::move( er ), std::move( aj ),
                          std::move( gn ), std::move( gg ),
                          std::move( gfa ), std::move( gfb ),
                          std::move( der ), std::move( dgn ),
                          std::move( dgg ), std::move( dgfa ),
                          std::move( dgfb ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different sizes" ) {

      double awri = 1.982069e+1;
      double apl = 15.;
      std::vector< double > wrong = { -1.470000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gg = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gfa = { 3., 4. };
      std::vector< double > gfb = { 5., 6. };
      std::vector< double > der = { 7., 8. };
      std::vector< double > dgn = { 9., 10. };
      std::vector< double > dgg = { 11., 12. };
      std::vector< double > dgfa = { 13., 14. };
      std::vector< double > dgfb = { 15., 16. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactReichMooreUncertainties(
                          awri, apl,
                          std::move( wrong ), std::move( aj ),
                          std::move( gn ), std::move( gg ),
                          std::move( gfa ), std::move( gfb ),
                          std::move( der ), std::move( dgn ),
                          std::move( dgg ), std::move( dgfa ),
                          std::move( dgfb ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRSA is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactReichMooreUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactReichMooreUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRS is used" ) {

      std::string string = noNumberResonances();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CompactReichMooreUncertainties( begin, end, lineNumber,
                                                       1025, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.982069+1 1.500000+1          0          0         24          2102532151     \n"
    "-1.470000+5 5.000000-1 3.680695+2 1.750000+2 3.000000+0 5.000000+0102532151     \n"
    " 7.000000+0 0.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072900+5 5.600000-1 4.000000+0 6.000000+0102532151     \n"
    " 8.000000+0 0.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n";
}

void verifyChunk( const CompactReichMooreUncertainties& chunk ) {

  CHECK( 1.982069e+1 == Approx( chunk.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 15. == Approx( chunk.APL() ) );
  CHECK( 15. == Approx( chunk.lDependentScatteringRadius() ) );

  CHECK( 2 == chunk.NRSA() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.AJ().size() );
  CHECK( 2 == chunk.spinValues().size() );
  CHECK( 2 == chunk.GN().size() );
  CHECK( 2 == chunk.neutronWidths().size() );
  CHECK( 2 == chunk.GG().size() );
  CHECK( 2 == chunk.gammaWidths().size() );
  CHECK( 2 == chunk.GFA().size() );
  CHECK( 2 == chunk.firstFissionWidths().size() );
  CHECK( 2 == chunk.GFB().size() );
  CHECK( 2 == chunk.secondFissionWidths().size() );
  CHECK( 2 == chunk.DER().size() );
  CHECK( 2 == chunk.resonanceEnergyUncertainties().size() );
  CHECK( 2 == chunk.DGN().size() );
  CHECK( 2 == chunk.neutronWidthUncertainties().size() );
  CHECK( 2 == chunk.DGG().size() );
  CHECK( 2 == chunk.gammaWidthUncertainties().size() );
  CHECK( 2 == chunk.DGFA().size() );
  CHECK( 2 == chunk.firstFissionWidthUncertainties().size() );
  CHECK( 2 == chunk.DGFB().size() );
  CHECK( 2 == chunk.secondFissionWidthUncertainties().size() );

  CHECK( -1.470000e+5 == Approx( chunk.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[0] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[1] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[0] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.GN()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.GN()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.neutronWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.neutronWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.GG()[0] ) );
  CHECK( 0.56 == Approx( chunk.GG()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.gammaWidths()[0] ) );
  CHECK( 0.56 == Approx( chunk.gammaWidths()[1] ) );
  CHECK( 3. == Approx( chunk.GFA()[0] ) );
  CHECK( 4. == Approx( chunk.GFA()[1] ) );
  CHECK( 3. == Approx( chunk.firstFissionWidths()[0] ) );
  CHECK( 4. == Approx( chunk.firstFissionWidths()[1] ) );
  CHECK( 5. == Approx( chunk.GFB()[0] ) );
  CHECK( 6. == Approx( chunk.GFB()[1] ) );
  CHECK( 5. == Approx( chunk.secondFissionWidths()[0] ) );
  CHECK( 6. == Approx( chunk.secondFissionWidths()[1] ) );

  CHECK( 7. == Approx( chunk.DER()[0] ) );
  CHECK( 8. == Approx( chunk.DER()[1] ) );
  CHECK( 7. == Approx( chunk.resonanceEnergyUncertainties()[0] ) );
  CHECK( 8. == Approx( chunk.resonanceEnergyUncertainties()[1] ) );
  CHECK( 9. == Approx( chunk.DGN()[0] ) );
  CHECK( 10. == Approx( chunk.DGN()[1] ) );
  CHECK( 9. == Approx( chunk.neutronWidthUncertainties()[0] ) );
  CHECK( 10. == Approx( chunk.neutronWidthUncertainties()[1] ) );
  CHECK( 11. == Approx( chunk.DGG()[0] ) );
  CHECK( 12. == Approx( chunk.DGG()[1] ) );
  CHECK( 11. == Approx( chunk.gammaWidthUncertainties()[0] ) );
  CHECK( 12. == Approx( chunk.gammaWidthUncertainties()[1] ) );
  CHECK( 13. == Approx( chunk.DGFA()[0] ) );
  CHECK( 14. == Approx( chunk.DGFA()[1] ) );
  CHECK( 13. == Approx( chunk.firstFissionWidthUncertainties()[0] ) );
  CHECK( 14. == Approx( chunk.firstFissionWidthUncertainties()[1] ) );
  CHECK( 15. == Approx( chunk.DGFB()[0] ) );
  CHECK( 16. == Approx( chunk.DGFB()[1] ) );
  CHECK( 15. == Approx( chunk.secondFissionWidthUncertainties()[0] ) );
  CHECK( 16. == Approx( chunk.secondFissionWidthUncertainties()[1] ) );

  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].ER() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].ER() ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].resonanceEnergy() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].resonanceEnergy() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].spin() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].spin() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].GN() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].GN() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].neutronWidth() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].neutronWidth() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].GG() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].GG() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].gammaWidth() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].gammaWidth() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].GFA() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].GFA() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].firstFissionWidth() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].firstFissionWidth() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].GFB() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].GFB() ) );
  CHECK( 5. == Approx( chunk.resonances()[0].secondFissionWidth() ) );
  CHECK( 6. == Approx( chunk.resonances()[1].secondFissionWidth() ) );

  CHECK( 7. == Approx( chunk.resonances()[0].DER() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].DER() ) );
  CHECK( 7. == Approx( chunk.resonances()[0].resonanceEnergyUncertainty() ) );
  CHECK( 8. == Approx( chunk.resonances()[1].resonanceEnergyUncertainty() ) );
  CHECK( 9. == Approx( chunk.resonances()[0].DGN() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].DGN() ) );
  CHECK( 9. == Approx( chunk.resonances()[0].neutronWidthUncertainty() ) );
  CHECK( 10. == Approx( chunk.resonances()[1].neutronWidthUncertainty() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].DGG() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].DGG() ) );
  CHECK( 11. == Approx( chunk.resonances()[0].gammaWidthUncertainty() ) );
  CHECK( 12. == Approx( chunk.resonances()[1].gammaWidthUncertainty() ) );
  CHECK( 13. == Approx( chunk.resonances()[0].DGFA() ) );
  CHECK( 14. == Approx( chunk.resonances()[1].DGFA() ) );
  CHECK( 13. == Approx( chunk.resonances()[0].firstFissionWidthUncertainty() ) );
  CHECK( 14. == Approx( chunk.resonances()[1].firstFissionWidthUncertainty() ) );
  CHECK( 15. == Approx( chunk.resonances()[0].DGFB() ) );
  CHECK( 16. == Approx( chunk.resonances()[1].DGFB() ) );
  CHECK( 15. == Approx( chunk.resonances()[0].secondFissionWidthUncertainty() ) );
  CHECK( 16. == Approx( chunk.resonances()[1].secondFissionWidthUncertainty() ) );

  CHECK( 5 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 1.500000+1          0          0         23          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1           102532151     \n";
}

std::string zeroSize() {
  return
    " 1.982069+1 1.500000+1          0          0          0          2102532151     \n";
}

std::string noNumberResonances() {
  return
    " 1.982069+1 1.500000+1          0          0         24          0102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n";
}
