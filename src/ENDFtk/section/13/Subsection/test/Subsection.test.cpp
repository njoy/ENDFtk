#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;
std::string sSubSection();

SCENARIO( "section::Type< 13 >::SubSection" ){
  GIVEN( "a string representation of a valid MF=13 Subsection" ){
    std::string sSS = sSubSection();
    // njoy::Log::info("sSS:\n{}", sSS );
    auto begin = sSS.begin();
    auto end = sSS.end();
    long lineNumber = 1;
    int MAT = 825;
    int MF = 13;
    int MT = 22;

    WHEN( "a section::Type< 13 >::SubSection is constructed" ){
      section::Type< 13 >::Subsection SS( begin, end, lineNumber, MAT, MT );
      std::vector< double > refEnergies{7.613591E+6, 1.233300E+7, 1.235000E+7, 
                                     1.245000E+7, 1.250000E+7, 1.255000E+7, 
                                     3.000001E+7, 1.500000E+8};
      std::vector< double > refXS{0.000000E+0, 0.000000E+0, 5.77776E-12, 
                                  1.012810E-7, 6.481624E-6, 1.905763E-4, 
                                  0.000000E+0, 0.000000E+0};

      THEN( "The subsection members can be verified" ){
        REQUIRE( Approx( 4.438E6 ) == SS.EG() );
        REQUIRE( Approx( 4.458E6 ) == SS.EK() );
        REQUIRE( 0 == SS.LP() );
        REQUIRE( 2 == SS.LF() );

        std::vector< double > energies = SS.energies();
        std::vector< double > XS = SS.crossSections();
        REQUIRE( refEnergies == energies );
        REQUIRE( refXS == XS );

        REQUIRE( 5 == SS.NC() );
      }

      THEN( "it can be printed" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        SS.print( output, 825, 22 );
        REQUIRE( buffer == sSS );
      }
    }
    WHEN( "there is a wrong MAT number" ){
      MAT = 1825;
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
          section::Type< 13 >::Subsection( begin, end, lineNumber, MAT, MT ) );
      }
    }
  }
}

std::string sSubSection() {
  return
    " 4.438000+6 4.458000+6          0          2          1          8 82513 22     \n"
    "          8          2                                             82513 22     \n"
    " 7.613591+6 0.000000+0 1.233300+7 0.000000+0 1.235000+7 5.77776-12 82513 22     \n"
    " 1.245000+7 1.012810-7 1.250000+7 6.481624-6 1.255000+7 1.905763-4 82513 22     \n"
    " 3.000001+7 0.000000+0 1.500000+8 0.000000+0                       82513 22     \n";
}

