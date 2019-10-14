#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ReichMoore =
resonanceParameters::resolved::ReichMoore;
using ReichMooreLValue =
resonanceParameters::resolved::ReichMooreLValue;

std::string chunk();
void verifyChunk( const ReichMoore& );
std::string invalidSize();

SCENARIO( "ReichMoore" ) {

  GIVEN( "valid data for a ReichMoore" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 1.0;
      double ap = 0.893;
      bool lad = false;
      int nlsc = 3;
      std::vector< ReichMooreLValue > lvalues = 
        { { 1.982069e+1, 0.0, 0,
            { -1.470000e+5, 4.730000e+5 }, { 0.5, 0.5 },
            { 5.430695e+2, 1.072906e+5 }, { 3.680695e+2, 1.072900e+5 },
            { 1.750000e+2, 5.600000e-1 }, { 3., 4. } },
          { 1.982069e+1, 0.0, 1,
            { -2.060000e+0, 5.160000+0 }, { 0.5, 0.5 },
            { 3.006610e-2, 3.393822e-2 }, { 5.750000e-3, 3.920000e-3 },
            { 2.430000e-2, 3.000000e-2 }, { 1.610000e-5, 1.822000e-5 } } };

      ReichMoore chunk( spi, ap, lad, nlsc, std::move( lvalues ) );

      THEN( "a ReichMoore can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReichMoore chunk( begin, end, lineNumber, 1025, 2, 151 );

      THEN( "a ReichMoore can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 8.930000-1          0          0          2          31025 2151     \n"
    " 1.982069+1 0.000000+0          0          0         12          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n"
    " 1.982069+1 0.000000+0          1          0         12          21025 2151     \n"
    "-2.060000+0 5.000000-1 3.006610-2 5.750000-3 2.430000-2 1.610000-51025 2151     \n"
    " 5.160000+0 5.000000-1 3.393822-2 3.920000-3 3.000000-2 1.822000-51025 2151     \n";
}

void verifyChunk( const ReichMoore& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 3 == chunk.LRF() );
  CHECK( 3 == chunk.representation() );

  CHECK( 1. == Approx( chunk.SPI() ) );
  CHECK( 1. == Approx( chunk.spin() ) );
  CHECK( 0.893 == Approx( chunk.AP() ) );
  CHECK( 0.893 == Approx( chunk.scatteringRadius() ) );

  CHECK( false == chunk.LAD() );
  CHECK( false == chunk.angularDistributionsFlag() );
  CHECK( 2 == chunk.NLS() );
  CHECK( 2 == chunk.numberLValues() );
  CHECK( 3 == chunk.NLSC() );
  CHECK( 3 == chunk.numberLValuesForConvergence() );

  CHECK( 2 == chunk.lValues().size() );

  auto lvalue1 = chunk.lValues()[0];
  CHECK( 1.982069e+1 == Approx( lvalue1.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( lvalue1.atomicWeightRatio() ) );
  CHECK( 0. == Approx( lvalue1.APL() ) );
  CHECK( 0. == Approx( lvalue1.lDependentScatteringRadius() ) );
  CHECK( 0 == lvalue1.L() );
  CHECK( 0 == lvalue1.orbitalMomentum() );

  CHECK( 2 == lvalue1.NRS() );
  CHECK( 2 == lvalue1.numberResonances() );
  CHECK( 2 == lvalue1.ER().size() );
  CHECK( 2 == lvalue1.resonanceEnergies().size() );
  CHECK( 2 == lvalue1.AJ().size() );
  CHECK( 2 == lvalue1.spinValues().size() );
  CHECK( 2 == lvalue1.GN().size() );
  CHECK( 2 == lvalue1.neutronWidths().size() );
  CHECK( 2 == lvalue1.GG().size() );
  CHECK( 2 == lvalue1.gammaWidths().size() );
  CHECK( 2 == lvalue1.GFA().size() );
  CHECK( 2 == lvalue1.firstFissionWidths().size() );
  CHECK( 2 == lvalue1.GFB().size() );
  CHECK( 2 == lvalue1.secondFissionWidths().size() );
  CHECK( 2 == lvalue1.resonances().size() );

  CHECK( -1.470000e+5 == Approx( lvalue1.ER()[0] ) );
  CHECK(  4.730000e+5 == Approx( lvalue1.ER()[1] ) );
  CHECK( -1.470000e+5 == Approx( lvalue1.resonanceEnergies()[0] ) );
  CHECK(  4.730000e+5 == Approx( lvalue1.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( lvalue1.AJ()[0] ) );
  CHECK( 0.5 == Approx( lvalue1.AJ()[1] ) );
  CHECK( 0.5 == Approx( lvalue1.spinValues()[0] ) );
  CHECK( 0.5 == Approx( lvalue1.spinValues()[1] ) );
  CHECK( 5.430695e+2 == Approx( lvalue1.GN()[0] ) );
  CHECK( 1.072906e+5 == Approx( lvalue1.GN()[1] ) );
  CHECK( 5.430695e+2 == Approx( lvalue1.neutronWidths()[0] ) );
  CHECK( 1.072906e+5 == Approx( lvalue1.neutronWidths()[1] ) );
  CHECK( 3.680695e+2 == Approx( lvalue1.GG()[0] ) );
  CHECK( 1.072900e+5 == Approx( lvalue1.GG()[1] ) );
  CHECK( 3.680695e+2 == Approx( lvalue1.gammaWidths()[0] ) );
  CHECK( 1.072900e+5 == Approx( lvalue1.gammaWidths()[1] ) );
  CHECK( 1.750000e+2 == Approx( lvalue1.GFA()[0] ) );
  CHECK( 0.56 == Approx( lvalue1.GFA()[1] ) );
  CHECK( 1.750000e+2 == Approx( lvalue1.firstFissionWidths()[0] ) );
  CHECK( 0.56 == Approx( lvalue1.firstFissionWidths()[1] ) );
  CHECK( 3. == Approx( lvalue1.GFB()[0] ) );
  CHECK( 4. == Approx( lvalue1.GFB()[1] ) );
  CHECK( 3. == Approx( lvalue1.secondFissionWidths()[0] ) );
  CHECK( 4. == Approx( lvalue1.secondFissionWidths()[1] ) );

  auto lvalue2 = chunk.lValues()[1];
  CHECK( 1.982069e+1 == Approx( lvalue2.AWRI() ) );
  CHECK( 1.982069e+1 == Approx( lvalue2.atomicWeightRatio() ) );
  CHECK( 0. == Approx( lvalue2.APL() ) );
  CHECK( 0. == Approx( lvalue2.lDependentScatteringRadius() ) );
  CHECK( 1 == lvalue2.L() );
  CHECK( 1 == lvalue2.orbitalMomentum() );

  CHECK( 2 == lvalue2.NRS() );
  CHECK( 2 == lvalue2.numberResonances() );
  CHECK( 2 == lvalue2.ER().size() );
  CHECK( 2 == lvalue2.resonanceEnergies().size() );
  CHECK( 2 == lvalue2.AJ().size() );
  CHECK( 2 == lvalue2.spinValues().size() );
  CHECK( 2 == lvalue2.GN().size() );
  CHECK( 2 == lvalue2.neutronWidths().size() );
  CHECK( 2 == lvalue2.GG().size() );
  CHECK( 2 == lvalue2.gammaWidths().size() );
  CHECK( 2 == lvalue2.GFA().size() );
  CHECK( 2 == lvalue2.firstFissionWidths().size() );
  CHECK( 2 == lvalue2.GFB().size() );
  CHECK( 2 == lvalue2.secondFissionWidths().size() );
  CHECK( 2 == lvalue2.resonances().size() );

  CHECK( -2.060000e+0 == Approx( lvalue2.ER()[0] ) );
  CHECK(  5.160000e+0 == Approx( lvalue2.ER()[1] ) );
  CHECK( -2.060000e+0 == Approx( lvalue2.resonanceEnergies()[0] ) );
  CHECK(  5.160000e+0 == Approx( lvalue2.resonanceEnergies()[1] ) );
  CHECK( 0.5 == Approx( lvalue2.AJ()[0] ) );
  CHECK( 0.5 == Approx( lvalue2.AJ()[1] ) );
  CHECK( 0.5 == Approx( lvalue2.spinValues()[0] ) );
  CHECK( 0.5 == Approx( lvalue2.spinValues()[1] ) );
  CHECK( 3.006610e-2 == Approx( lvalue2.GN()[0] ) );
  CHECK( 3.393822e-2 == Approx( lvalue2.GN()[1] ) );
  CHECK( 3.006610e-2 == Approx( lvalue2.neutronWidths()[0] ) );
  CHECK( 3.393822e-2 == Approx( lvalue2.neutronWidths()[1] ) );
  CHECK( 5.750000e-3 == Approx( lvalue2.GG()[0] ) );
  CHECK( 3.920000e-3 == Approx( lvalue2.GG()[1] ) );
  CHECK( 5.750000e-3 == Approx( lvalue2.gammaWidths()[0] ) );
  CHECK( 3.920000e-3 == Approx( lvalue2.gammaWidths()[1] ) );
  CHECK( 2.430000e-2 == Approx( lvalue2.GFA()[0] ) );
  CHECK( 3.000000e-2 == Approx( lvalue2.GFA()[1] ) );
  CHECK( 2.430000e-2 == Approx( lvalue2.firstFissionWidths()[0] ) );
  CHECK( 3.000000e-2 == Approx( lvalue2.firstFissionWidths()[1] ) );
  CHECK( 1.610000e-5 == Approx( lvalue2.GFB()[0] ) );
  CHECK( 1.822000e-5 == Approx( lvalue2.GFB()[1] ) );
  CHECK( 1.610000e-5 == Approx( lvalue2.secondFissionWidths()[0] ) );
  CHECK( 1.822000e-5 == Approx( lvalue2.secondFissionWidths()[1] ) );

  CHECK( 7 == chunk.NC() );
}




/*


SCENARIO( "Testing resolved Resonance ReichMoore" ){
  GIVEN( "valid ENDF parameters with TAB1" ){
      
    long lineNumber = 0;
    int MAT = 6922;
    int MF = 2;
    int MT = 151;

    WHEN( "NRO == 1" ){
      auto rms = Tab1() + cont() + ReichMoore();
      auto begin = rms.begin();
      auto end = rms.end();
      
      resonanceParameters::Base base( 1E-5, 4.0, 1, 3, 1, 0 );

      std::string baseString =
        " 1.000000-5 4.000000+0          1          3          1          06922 2151     \n";
      
      resonanceParameters::resolved::ReichMoore
        rm( base, begin, end, lineNumber, MAT, MF, MT );
      
      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == rm.EL() );
        REQUIRE( 4.0 == rm.EH() );
        REQUIRE( 1 == rm.NRO() );
        REQUIRE( 0 == rm.NAPS() );
        REQUIRE( 0 == rm.NAPS() );
        REQUIRE( 1 == rm.LRU() );
        REQUIRE( 3 == rm.LRF() );
        REQUIRE( 39 == rm.NC() );
        
        REQUIRE( 3.5 == rm.SPI() );
        REQUIRE( 0.98596 == Approx( rm.AP() ) );
        REQUIRE( 1 == rm.LAD() );
        REQUIRE( 1 == rm.NLS() );
        REQUIRE( 3 == rm.NLSC() );

        REQUIRE( 233.02 == Approx( rm.LISTS().front().C1() ) );
        REQUIRE( 0.98596 == rm.LISTS().front().C2() );
        REQUIRE( 0 == rm.LISTS().front().L1() );
        REQUIRE( 0 == rm.LISTS().front().L2() );
        REQUIRE( 102 == rm.LISTS().front().NPL() );
        REQUIRE( 23 == rm.LISTS().front().N2() );

        REQUIRE( 0.0 == rm.APE().C1() );
        REQUIRE( 0.0 == rm.APE().C2() );
        REQUIRE( 0 == rm.APE().L1() );
        REQUIRE( 0 == rm.APE().L2() );
        REQUIRE( 1 == rm.APE().NR() );
        REQUIRE( 50 == rm.APE().NP() );
        REQUIRE( 50 == rm.APE().x().size() );
        REQUIRE( 50 == rm.APE().y().size() );
        REQUIRE( 1.0E-5 == Approx( rm.APE().x().front() ) );
        REQUIRE( 1.2381 == Approx( rm.APE().y().front() ) );
        REQUIRE( 2.0E5 == Approx( rm.APE().x().back() ) );
        REQUIRE( 0.5803 == Approx( rm.APE().y().back() ) );
      }

      
      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        rm.print( output, MAT, MF, MT );

        REQUIRE( buffer == baseString + Tab1() + cont() + ReichMoore() );
      }
    }
    
    WHEN( "NRO == 0" ){
      auto rms = cont() + ReichMoore();
      auto begin = rms.begin();
      auto end = rms.end();
      
      resonanceParameters::Base base(1E-5, 3.2, 1, 3, 0, 0);
      std::string baseString =
        " 1.000000-5 3.200000+0          1          3          0          06922 2151     \n";
      
      resonanceParameters::resolved::ReichMoore
        rm( base, begin, end, lineNumber, MAT, MF, MT );

      THEN( "the parameters can be verified" ){
        REQUIRE( 1E-5 == rm.EL() );
        REQUIRE( 3.2 == rm.EH() );
        REQUIRE( 0 == rm.NRO() );
        REQUIRE( 0 == rm.NAPS() );
        REQUIRE( 1 == rm.LRU() );
        REQUIRE( 3 == rm.LRF() );
        REQUIRE( 20 == rm.NC() );
        
        REQUIRE( 3.5 == rm.SPI() );
        REQUIRE( 0.98596 == Approx( rm.AP() ) );
        REQUIRE( 1 == rm.LAD() );
        REQUIRE( 1 == rm.NLS() );
        REQUIRE( 3 == rm.NLSC() );

        REQUIRE( 233.02 == Approx( rm.LISTS().front().C1() ) );
        REQUIRE( 0.98596 == rm.LISTS().front().C2() );
        REQUIRE( 0 == rm.LISTS().front().L1() );
        REQUIRE( 0 == rm.LISTS().front().L2() );
        REQUIRE( 102 == rm.LISTS().front().NPL() );
        REQUIRE( 23 == rm.LISTS().front().N2() ); 
      }

      
      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        rm.print( output, MAT, MF, MT );

        REQUIRE( buffer == baseString + cont() + ReichMoore() );
      }
    }
  }

  GIVEN( "invalid ENDF parameters" ){
    long lineNumber = 0;
    int MAT = 6922;
    int MF = 2;
    int MT = 151;

    WHEN( "LAD value is invalid" ){
      std::string cont1 = " 3.500000+0 9.859600-1         -1          0          1          36922 2151\n";
      std::string cont2 = " 3.500000+0 9.859600-1          2          0          1          36922 2151\n";
      resonanceParameters::Base base(1E-5, 3.2, 1, 3, 0, 0);

      THEN( "an exception is thrown" ){
        std::string rms = cont1 + ReichMoore();
        auto begin = rms.begin();
        auto end = rms.end();
        REQUIRE_THROWS( resonanceParameters::resolved::ReichMoore( 
                          base, begin, end, lineNumber, MAT, MF, MT ) );
        rms = cont2 + ReichMoore();
        begin = rms.begin();
        end = rms.end();
        REQUIRE_THROWS( resonanceParameters::resolved::ReichMoore( 
                          base, begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "NLSC < NLS" ){
      std::string cont1 = " 3.500000+0 9.859600-1          1          0          4          36922 2151\n";
      resonanceParameters::Base base(1E-5, 3.2, 1, 3, 0, 0);

      THEN( "an exception is thrown" ){
        std::string rms = cont1 + ReichMoore();
        auto begin = rms.begin();
        auto end = rms.end();
        REQUIRE_THROWS( resonanceParameters::resolved::ReichMoore( 
                          base, begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
  }
}

std::string cont(){
  return
    " 3.500000+0 9.859600-1          1          0          1          36922 2151     \n";
}

std::string ReichMoore(){
  return
    " 2.330200+2 9.859600-1          0          0        102         236922 2151     \n"
    "-1.000000+2 3.000000+0 1.145800-2 3.871290-2 1.229980-4 7.233640-26922 2151     \n"
    "-9.000000+1 4.000000+0 2.422100-6 3.680760-2 5.617020-2-2.168940-16922 2151     \n"
    "-4.297600+0 4.000000+0 7.164100-3 3.481860-2 3.192990-1-1.153500-16922 2151     \n"
    "-3.493400+0 3.000000+0 8.471500-8 3.780160-2-6.760010-3 1.298560-26922 2151     \n"
    "-1.504300+0 3.000000+0 8.519600-8 3.767610-2-7.010690-3 1.232090-26922 2151     \n"
    "-4.116100-1 3.000000+0 1.487500-4 2.984470-2-1.027260-3-1.554150-16922 2151     \n"
    "-1.942800-1 4.000000+0 5.044600-7 3.504170-2 1.989540-1-1.694210-36922 2151     \n"
    " 3.657500-5 4.000000+0 6.50520-11 2.984470-2-5.263430-4 9.645560-46922 2151     \n"
    " 2.819000-1 3.000000+0 4.439200-6 3.837130-2 1.065400-1-4.849860-36922 2151     \n"
    " 1.138900+0 4.000000+0 1.384200-5 4.069500-2-4.640000-6 1.093200-16922 2151     \n"
    " 2.036100+0 3.000000+0 9.358700-6 3.933000-2-7.736600-3-1.573500-36922 2151     \n"
    " 2.776700+0 4.000000+0 1.277200-6 3.887600-2 6.049200-2-4.250300-26922 2151     \n"
    " 3.156600+0 3.000000+0 2.432600-5 3.989600-2-7.995100-2 1.716100-26922 2151     \n"
    " 3.620800+0 4.000000+0 4.184000-5 3.764400-2-2.679600-2 2.849100-26922 2151     \n"
    " 4.850800+0 4.000000+0 7.560500-5 3.801700-2 4.666800-5-3.735100-36922 2151     \n"
    " 5.449700+0 4.000000+0 3.793200-5 3.920100-2-7.874000-2-3.612500-16922 2151     \n"
    " 6.209400+0 3.000000+0 1.654700-4 4.005100-2-1.079400-1 7.385900-26922 2151     \n";
}

std::string Tab1(){
  return
  " 0.000000+0 0.000000+0          0          0          1         506922 2151     \n"
  "         50          2                                            6922 2151     \n"
  " 1.000000-5 1.238100+0 4.000000+1 1.188400+0 5.000000+1 1.153200+06922 2151     \n"
  " 6.000000+1 1.126500+0 7.000000+1 1.105300+0 8.000000+1 1.087800+06922 2151     \n"
  " 9.000000+1 1.073100+0 1.000000+2 1.060500+0 2.000000+2 9.888000-16922 2151     \n"
  " 3.000000+2 9.547000-1 4.000000+2 9.334000-1 5.000000+2 9.184000-16922 2151     \n"
  " 6.000000+2 9.069000-1 7.000000+2 8.978000-1 8.000000+2 8.903000-16922 2151     \n"
  " 9.000000+2 8.839000-1 1.000000+3 8.783000-1 2.000000+3 8.456000-16922 2151     \n"
  " 3.000000+3 8.286000-1 4.000000+3 8.170000-1 5.000000+3 8.081000-16922 2151     \n"
  " 6.000000+3 8.008000-1 7.000000+3 7.946000-1 8.000000+3 7.892000-16922 2151     \n"
  " 9.000000+3 7.844000-1 1.000000+4 7.800000-1 1.200000+4 7.721000-16922 2151     \n"
  " 1.400000+4 7.653000-1 1.600000+4 7.592000-1 1.800000+4 7.536000-16922 2151     \n"
  " 2.000000+4 7.484000-1 2.500000+4 7.369000-1 3.000000+4 7.269000-16922 2151     \n"
  " 3.500000+4 7.180000-1 4.000000+4 7.098000-1 4.200000+4 7.067000-16922 2151     \n"
  " 4.400000+4 7.038000-1 4.600000+4 7.009000-1 4.800000+4 6.980000-16922 2151     \n"
  " 5.000000+4 6.953000-1 5.500000+4 6.888000-1 6.000000+4 6.826000-16922 2151     \n"
  " 6.500000+4 6.767000-1 7.000000+4 6.712000-1 7.500000+4 6.659000-16922 2151     \n"
  " 8.000000+4 6.608000-1 8.500000+4 6.560000-1 9.000000+4 6.513000-16922 2151     \n"
  " 9.500000+4 6.469000-1 2.000000+5 5.803000-1                      6922 2151     \n";
}*/
