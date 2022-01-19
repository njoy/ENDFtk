#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/32/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ShortRangeReichMooreBlock =
section::Type< 32, 151 >::ShortRangeReichMooreBlock;

std::string chunk();
void verifyChunk( const ShortRangeReichMooreBlock& );
std::string invalidSize();
std::string zeroSize();
std::string noNumberResonances();

SCENARIO( "ShortRangeReichMooreBlock" ) {

  GIVEN( "valid data for a ShortRangeReichMooreBlock" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double awri = 1.982069e+1;
      int mpar = 4;
      std::vector< double > er = { -1.470000e+5, 4.730000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gg = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gfa = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gfb = { 3., 4. };
      std::vector< double > values = {  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                            13., 14., 15., 16., 17., 18., 19.,
                                                 20., 21., 22., 23., 24., 25.,
                                                      26., 27., 28., 29., 30.,
                                                           31., 32., 33., 34.,
                                                                35., 36., 37.,
                                                                     38., 39.,
                                                                          40. };

      ShortRangeReichMooreBlock chunk( awri, mpar,
                                       std::move( er ), std::move( aj ),
                                       std::move( gn ), std::move( gg ),
                                       std::move( gfa ), std::move( gfb ),
                                       std::move( values ) );

      THEN( "a ShortRangeReichMooreBlock can be constructed and members can be "
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

      ShortRangeReichMooreBlock chunk( begin, end, lineNumber, 1025, 32, 151 );

      THEN( "a ShortRangeReichMooreBlock can be constructed and members can be "
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
      int mpar = 4;
      std::vector< double > er = {};
      std::vector< double > aj = {};
      std::vector< double > gn = {};
      std::vector< double > gg = {};
      std::vector< double > gfa = {};
      std::vector< double > gfb = {};
      std::vector< double > values = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ShortRangeReichMooreBlock(
                          awri, mpar,
                          std::move( er ), std::move( aj ),
                          std::move( gn ), std::move( gg ),
                          std::move( gfa ), std::move( gfb ),
                          std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data has different sizes" ) {

      double awri = 1.982069e+1;
      int mpar = 4;
      std::vector< double > wrong = { -1.470000e+5 };
      std::vector< double > aj = { 0.5, 0.5 };
      std::vector< double > gn = { 5.470695e+2, 1.072946e+5 };
      std::vector< double > gg = { 3.680695e+2, 1.072900e+5 };
      std::vector< double > gfa = { 1.750000e+2, 5.600000e-1 };
      std::vector< double > gfb = { 3., 4. };
      std::vector< double > values = {  5.,  6.,  7.,  8.,  9., 10., 11., 12.,
                                            13., 14., 15., 16., 17., 18., 19.,
                                                 20., 21., 22., 23., 24., 25.,
                                                      26., 27., 28., 29., 30.,
                                                           31., 32., 33., 34.,
                                                                35., 36., 37.,
                                                                     38., 39.,
                                                                          40. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ShortRangeReichMooreBlock(
                          awri, mpar,
                          std::move( wrong ), std::move( aj ),
                          std::move( gn ), std::move( gg ),
                          std::move( gfa ), std::move( gfb ),
                          std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRB is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ShortRangeReichMooreBlock( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with zero NPL" ) {

      std::string string = zeroSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ShortRangeReichMooreBlock( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN

    WHEN( "a string with inconsistent NPL and NRB is used" ) {

      std::string string = noNumberResonances();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ShortRangeReichMooreBlock( begin, end, lineNumber, 1025, 32, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.982069+1 0.000000+0          4          0         48          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}

void verifyChunk( const ShortRangeReichMooreBlock& chunk ) {

  CHECK( 1.982069e+1 == Approx( chunk.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 4 == chunk.MPAR() );
  CHECK( 4 == chunk.numberParametersWithCovariances() );

  CHECK( 2 == chunk.NRB() );
  CHECK( 2 == chunk.numberResonances() );
  CHECK( 2 == chunk.ER().size() );
  CHECK( 2 == chunk.resonanceEnergies().size() );
  CHECK( 2 == chunk.AJ().size() );
  CHECK( 2 == chunk.spinValues().size() );
  CHECK( 2 == chunk.GN().size() );
  CHECK( 2 == chunk.gammaWidths().size() );
  CHECK( 2 == chunk.GG().size() );
  CHECK( 2 == chunk.firstFissionWidths().size() );
  CHECK( 2 == chunk.GFA().size() );
  CHECK( 2 == chunk.firstFissionWidths().size() );
  CHECK( 2 == chunk.GFB().size() );
  CHECK( 2 == chunk.secondFissionWidths().size() );

  CHECK( -1.470000e+5 == Approx( chunk.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[0] ) );
  CHECK( 0.5 == Approx( chunk.AJ()[1] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[0] ) );
  CHECK( 0.5 == Approx( chunk.spinValues()[1] ) );
  CHECK( 5.470695e+2 == Approx( chunk.GN()[0] ) );
  CHECK( 1.072946e+5 == Approx( chunk.GN()[1] ) );
  CHECK( 5.470695e+2 == Approx( chunk.neutronWidths()[0] ) );
  CHECK( 1.072946e+5 == Approx( chunk.neutronWidths()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.GG()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.GG()[1] ) );
  CHECK( 3.680695e+2 == Approx( chunk.gammaWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( chunk.gammaWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.GFA()[0] ) );
  CHECK( 0.56 == Approx( chunk.GFA()[1] ) );
  CHECK( 1.750000e+2 == Approx( chunk.firstFissionWidths()[0] ) );
  CHECK( 0.56 == Approx( chunk.firstFissionWidths()[1] ) );
  CHECK( 3. == Approx( chunk.GFB()[0] ) );
  CHECK( 4. == Approx( chunk.GFB()[1] ) );
  CHECK( 3. == Approx( chunk.secondFissionWidths()[0] ) );
  CHECK( 4. == Approx( chunk.secondFissionWidths()[1] ) );

  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].ER() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].ER() ) );
  CHECK( -1.470000e+5 == Approx( chunk.resonances()[0].resonanceEnergy() ) );
  CHECK(  4.730000e+5 == Approx( chunk.resonances()[1].resonanceEnergy() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].AJ() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[0].spin() ) );
  CHECK( 0.5 == Approx( chunk.resonances()[1].spin() ) );
  CHECK( 5.470695e+2 == Approx( chunk.resonances()[0].GN() ) );
  CHECK( 1.072946e+5 == Approx( chunk.resonances()[1].GN() ) );
  CHECK( 5.470695e+2 == Approx( chunk.resonances()[0].neutronWidth() ) );
  CHECK( 1.072946e+5 == Approx( chunk.resonances()[1].neutronWidth() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].GG() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].GG() ) );
  CHECK( 3.680695e+2 == Approx( chunk.resonances()[0].gammaWidth() ) );
  CHECK( 1.072900e+5 == Approx( chunk.resonances()[1].gammaWidth() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].GFA() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].GFA() ) );
  CHECK( 1.750000e+2 == Approx( chunk.resonances()[0].firstFissionWidth() ) );
  CHECK( 0.56 == Approx( chunk.resonances()[1].firstFissionWidth() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].GFB() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].GFB() ) );
  CHECK( 3. == Approx( chunk.resonances()[0].secondFissionWidth() ) );
  CHECK( 4. == Approx( chunk.resonances()[1].secondFissionWidth() ) );

  CHECK( 8 == chunk.covarianceMatrixOrder() );
  CHECK( 36 == chunk.covarianceMatrix().size() );
  CHECK( 36 == chunk.NVS() );
  CHECK( 36 == chunk.numberValues() );

  CHECK(  5. == Approx( chunk.covarianceMatrix()[ 0] ) );
  CHECK(  6. == Approx( chunk.covarianceMatrix()[ 1] ) );
  CHECK(  7. == Approx( chunk.covarianceMatrix()[ 2] ) );
  CHECK(  8. == Approx( chunk.covarianceMatrix()[ 3] ) );
  CHECK(  9. == Approx( chunk.covarianceMatrix()[ 4] ) );
  CHECK( 10. == Approx( chunk.covarianceMatrix()[ 5] ) );
  CHECK( 11. == Approx( chunk.covarianceMatrix()[ 6] ) );
  CHECK( 12. == Approx( chunk.covarianceMatrix()[ 7] ) );
  CHECK( 13. == Approx( chunk.covarianceMatrix()[ 8] ) );
  CHECK( 14. == Approx( chunk.covarianceMatrix()[ 9] ) );
  CHECK( 15. == Approx( chunk.covarianceMatrix()[10] ) );
  CHECK( 16. == Approx( chunk.covarianceMatrix()[11] ) );
  CHECK( 17. == Approx( chunk.covarianceMatrix()[12] ) );
  CHECK( 18. == Approx( chunk.covarianceMatrix()[13] ) );
  CHECK( 19. == Approx( chunk.covarianceMatrix()[14] ) );
  CHECK( 20. == Approx( chunk.covarianceMatrix()[15] ) );
  CHECK( 21. == Approx( chunk.covarianceMatrix()[16] ) );
  CHECK( 22. == Approx( chunk.covarianceMatrix()[17] ) );
  CHECK( 23. == Approx( chunk.covarianceMatrix()[18] ) );
  CHECK( 24. == Approx( chunk.covarianceMatrix()[19] ) );
  CHECK( 25. == Approx( chunk.covarianceMatrix()[20] ) );
  CHECK( 26. == Approx( chunk.covarianceMatrix()[21] ) );
  CHECK( 27. == Approx( chunk.covarianceMatrix()[22] ) );
  CHECK( 28. == Approx( chunk.covarianceMatrix()[23] ) );
  CHECK( 29. == Approx( chunk.covarianceMatrix()[24] ) );
  CHECK( 30. == Approx( chunk.covarianceMatrix()[25] ) );
  CHECK( 31. == Approx( chunk.covarianceMatrix()[26] ) );
  CHECK( 32. == Approx( chunk.covarianceMatrix()[27] ) );
  CHECK( 33. == Approx( chunk.covarianceMatrix()[28] ) );
  CHECK( 34. == Approx( chunk.covarianceMatrix()[29] ) );
  CHECK( 35. == Approx( chunk.covarianceMatrix()[30] ) );
  CHECK( 36. == Approx( chunk.covarianceMatrix()[31] ) );
  CHECK( 37. == Approx( chunk.covarianceMatrix()[32] ) );
  CHECK( 38. == Approx( chunk.covarianceMatrix()[33] ) );
  CHECK( 39. == Approx( chunk.covarianceMatrix()[34] ) );
  CHECK( 40. == Approx( chunk.covarianceMatrix()[35] ) );

  CHECK( 9 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.982069+1 0.000000+0          4          0         47          2102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1           102532151     \n";
}

std::string zeroSize() {
  return
    " 1.982069+1 0.000000+0          0          0          0          21025 2151     \n";
}

std::string noNumberResonances() {
  return
    " 1.982069+1 0.000000+0          4          0         48          0102532151     \n"
    "-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n"
    " 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n"
    " 5.000000+0 6.000000+0 7.000000+0 8.000000+0 9.000000+0 1.000000+1102532151     \n"
    " 1.100000+1 1.200000+1 1.300000+1 1.400000+1 1.500000+1 1.600000+1102532151     \n"
    " 1.700000+1 1.800000+1 1.900000+1 2.000000+1 2.100000+1 2.200000+1102532151     \n"
    " 2.300000+1 2.400000+1 2.500000+1 2.600000+1 2.700000+1 2.800000+1102532151     \n"
    " 2.900000+1 3.000000+1 3.100000+1 3.200000+1 3.300000+1 3.400000+1102532151     \n"
    " 3.500000+1 3.600000+1 3.700000+1 3.800000+1 3.900000+1 4.000000+1102532151     \n";
}
