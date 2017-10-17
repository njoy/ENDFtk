#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

std::string baseSection();
std::string invalidBaseSection();
std::string validSEND();
std::string invalidSEND();

using namespace njoy::ENDFtk;

SCENARIO( "section::Type<13>" ){
  GIVEN( "a string representation of a valid File 13 Section" ){
    std::vector<double> referenceEnergy =
      { 7.613591E+6, 1.233300E+7, 1.235000E+7, 1.245000E+7,
        1.250000E+7, 1.255000E+7, 3.000001E+7, 1.500000E+8 };

    std::vector<double> referenceCrossSection =
      { 0.000000E+0,  0.000000E+0, 5.77776E-12, 1.012810E-7,
        6.481624E-6, 1.905763E-4, 0.000000E+0,  0.000000E+0 };

    WHEN( "NK = 1" ){
      std::string sHead =
        " 8.016000+3 1.585751+1          0          0          1          0 82513 22\n";

      std::string sectionString = sHead + baseSection() + validSEND();

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;

      HeadRecord head( begin, end, lineNumber );

      THEN( "a section::Type<13> can be constructed and members can be tested" ){
        section::Type< 13 > MF13( head, begin, end, lineNumber, 825 );

        REQUIRE( 22 == MF13.MT() );
        REQUIRE( 8016 == MF13.ZA() );
        REQUIRE( Approx(15.85751) == MF13.atomicWeightRatio() );
        REQUIRE( 1 == MF13.NK() );

        REQUIRE( ranges::equal( MF13.energies(), referenceEnergy ) );
        REQUIRE( ranges::equal( MF13.crossSections(), referenceCrossSection ) );
      }
    } // WHEN

    WHEN( "creating an intermediate syntaxTree::Section" ){
      std::string sHead =
        " 8.016000+3 1.585751+1          0          0          1          0 82513 22\n";

      std::string sectionString = sHead + baseSection() + validSEND();

      auto begin = sectionString.begin();
      auto position = begin;
      auto end = sectionString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );

      syntaxTree::Section< std::string::iterator>
        mf13( head, begin, position, end, lineNumber );

      THEN( "a section::Type<13> can be constructed and members can be tested" ){
        section::Type< 13 > MF13 = mf13.parse< 13 >( lineNumber, 825 );

        REQUIRE( 22 == MF13.MT() );
        REQUIRE( 8016 == MF13.ZA() );
        REQUIRE( Approx(15.85751) == MF13.atomicWeightRatio() );
        REQUIRE( 1 == MF13.NK() );

        REQUIRE( ranges::equal( MF13.energies(), referenceEnergy ) );
        REQUIRE( ranges::equal( MF13.crossSections(), referenceCrossSection ) );
      }
    }

    WHEN( "NK = 2" ){
      std::string sHead =
        " 8.016000+3 1.585751+1          0          0          2          0 82513 22\n";

      std::string sectionString =
        sHead + baseSection() + baseSection() + baseSection() + validSEND();

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;

      HeadRecord head( begin, end, lineNumber );

      std::vector< double > refEnergies{ 7.613591E+6, 1.233300E+7, 1.235000E+7,
                                         1.245000E+7, 1.250000E+7, 1.255000E+7,
                                         3.000001E+7, 1.500000E+8};

      std::vector< double > refXS{ 0.000000E+0, 0.000000E+0, 5.77776E-12,
                                   1.012810E-7, 6.481624E-6, 1.905763E-4,
                                   0.000000E+0, 0.000000E+0};
      THEN( "a section::Type<13> can be constructed and members can be tested" ){
        section::Type< 13 > MF13( head, begin, end, lineNumber, 825 );

        REQUIRE( 22 == MF13.MT() );
        REQUIRE( 8016 == MF13.ZA() );
        REQUIRE( Approx(15.85751) == MF13.atomicWeightRatio() );
        REQUIRE( 2 == MF13.NK() );

        REQUIRE( 2 == MF13.subsections().size() );

        auto energies = MF13.energies();
        auto XS = MF13.crossSections();
        REQUIRE( ranges::equal( refEnergies, energies ) );
        REQUIRE( ranges::equal( refXS, XS ) );
      }
    } // WHEN

    WHEN( "NK is wrong" ){
      std::string sHead =
        " 8.016000+3 1.585751+1          0          0          2          0 82513 22\n";

      std::string sectionString =
        sHead + baseSection() + baseSection() + validSEND();

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( section::Type< 13 >( head, begin, end, lineNumber, 825 ) );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string baseSection(){
  return
    // " 8.016000+3 1.585751+1          0          0          1          0 82513 22\n"
    " 4.438000+6 4.438000+6          0          2          1          8 82513 22\n"
    "          8          2                                             82513 22\n"
    " 7.613591+6 0.000000+0 1.233300+7 0.000000+0 1.235000+7 5.77776-12 82513 22\n"
    " 1.245000+7 1.012810-7 1.250000+7 6.481624-6 1.255000+7 1.905763-4 82513 22\n"
    " 3.000001+7 0.000000+0 1.500000+8 0.000000+0                       82513 22     \n";
}

std::string validSEND(){
  return
    "                                                                   82513  0\n";
}
