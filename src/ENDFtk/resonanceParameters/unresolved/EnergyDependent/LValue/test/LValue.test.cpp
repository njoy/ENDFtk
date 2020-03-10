#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using JValue = resonanceParameters::unresolved::EnergyDependent::JValue;
using LValue = resonanceParameters::unresolved::EnergyDependent::LValue;

std::string chunk();
void verifyChunk( const LValue& );

SCENARIO( "LValue" ) {

  GIVEN( "valid data for an LValue" ) {

    std::string string = chunk();

    /*WHEN( "the data is given explicitly" ) {

      double spin = 0.0;
      double ap = 0.6233;
      bool lssf = false;

      std::vector< LValue > lvalues =
        { { 138.709, 0,
            { 0.5 }, { 4400. }, { 1 }, { 0.44 }, { 0.05 } },
          { 138.709, 1,
            { 0.5, 1.5 }, { 4400., 2200. }, { 1, 1 }, { 0.528, 0.264 },
            { 0.09, 0.091 } },
          { 138.709, 2,
            { 1.5, 2.5 }, { 2200., 1466.67 }, { 1, 1 }, { 0.033, 0.022 },
            { 0.05, 0.051 } } };

      LValue chunk( spin, ap, lssf, std::move( lvalues ) );

      THEN( "a LValue can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
*/
    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LValue chunk( begin, end, lineNumber, 3843, 2, 151 );

      THEN( "a LValue can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 3843, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 8.913540+1 0.000000+0          1          0          2          03843 2151     \n"
    " 5.000000-1 0.000000+0          5          0         24          33843 2151     \n"
    " 0.000000+0 0.000000+0 4.000000+0 3.000000+0 2.000000+0 1.000000+03843 2151     \n"
    " 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n"
    " 1.500000+0 0.000000+0          5          0         18          23843 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 1.000000+0 4.000000+0 2.000000+03843 2151     \n"
    " 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n"
    " 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n";
}

void verifyChunk( const LValue& chunk ) {

  CHECK( 89.1354 == Approx( chunk.AWRI() ) );
  CHECK( 89.1354 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 1 == chunk.L() );
  CHECK( 1 == chunk.orbitalMomentum() );
  CHECK( 2 == chunk.NJS() );
  CHECK( 2 == chunk.numberSpinValues() );

  auto jvalue10 = chunk.jValues()[0];

  auto jvalue11 = chunk.jValues()[1];

  CHECK( 10 == chunk.NC() );
}
