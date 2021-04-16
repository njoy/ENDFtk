#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/file/1.hpp"

// other includes
#include "ENDFtk/tree/File.hpp"
#include "range/v3/algorithm/count.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunk1();
std::string chunk451();
void verifyChunk451( const file::Type< 1 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();
std::string validHEAD();

SCENARIO( "Testing special case of file 1" ) {

  GIVEN( "valid data for a File 1" ) {

    double za = 39088.;
    double awr = 87.15432;
    int lrp = 0;
    int lfi = 0;
    int nlib = 0;
    int nmod = 0;
    double elis = 0.0;
    double sta = 0;
    int lis = 0;
    int liso =0;
    int nfor = 6;
    double awi = 1.0;
    double emax = 2e+7;
    int lrel = 0;
    int nsub = 10;
    int nver = 0;
    double temp = 293.6;
    int ldrv = 1;
    std::string description =
        " 39- Y- 88 LANL                                                   \n"
        "LANL                                                              \n"
        "----LANL/RC-III       MATERIAL 3988                               \n"
        "-----INCIDENT NEUTRON DATA                                        \n"
        "------ENDF-6 FORMAT                                               \n"
        "***************************************************               \n";
    int nc = 4 + ranges::cpp20::count( description, '\n' ) + 2;

    WHEN( "a file::Type< 1 > is constructed using only mt451" ) {

      section::Type< 1, 451 > mt451( za, awr, lrp, lfi, nlib, nmod,
                                     elis, sta, lis, liso, nfor,
                                     awi, emax, lrel, nsub, nver,
                                     temp, ldrv,
                                     description,
                                     { { 1, 451, nc, 0 },
                                       { 3, 1, 4, 0 } } );

      file::Type< 1 > mf1( std::move( mt451 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk451( mf1 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf1.print( output, 3988 );

        CHECK( buffer == chunk451() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 1 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      std::string string = chunk451() + validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      std::string string = chunk451() + validMEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      std::string string = chunk451() + validTEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a HEAD instead of FEND" ) {

      std::string string = chunk451() + validHEAD();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 1 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string file1string = chunk1();

  GIVEN( "a string representation of of File 1" ) {

    WHEN( "a file::Type< 1 > is constructed from the string" ) {

      auto begin = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision head( begin, end, lineNumber );
      file::Type< 1 > file( head, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        CHECK( file.hasMT( 451 ) );
        CHECK( not file.hasMT( 1 ) );
        CHECK( file.hasSection( 451 ) );
        CHECK( not file.hasSection( 1 ) );

        CHECK( 1001. == Approx( file.section( 451_c ).ZA() ) );
        CHECK( 1001. == Approx( file.MT( 451_c ).ZA() ) );
      }

      THEN( "the sections can be extracted" ) {

        CHECK_NOTHROW( file.MT( 451_c ) );
      }

      THEN( "an exception is thrown if invalid MT" ) {

        CHECK_THROWS( file.MT( 452_c ) );
        CHECK_THROWS( file.MT( 455_c ) );
        CHECK_THROWS( file.MT( 456_c ) );
        CHECK_THROWS( file.MT( 458_c ) );
        CHECK_THROWS( file.MT( 460_c ) );
      }
    }

    WHEN( "a file::Type< 1 > is constructed from a syntaxTree" ) {
      auto begin = file1string.begin();
      auto start = file1string.begin();
      auto end = file1string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      tree::File< std::string::iterator >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 1 > can be constructed" ){
        CHECK_NOTHROW( fileTree.parse< 1 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 1 > is constructed from the string twice" ){
      std::string twice( file1string.begin(), file1string.end() - 81 );
      twice += file1string;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );
      THEN( "an exception is thrown" ){
        CHECK_THROWS( file::Type< 1 >
                        ( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 1 >" ) {
    auto begin = file1string.begin();
    auto end = file1string.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 1 > file1( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file1.print( output, 125 );
      CHECK( buffer == file1string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0        108         10 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "Covariance Data Updated                                    G.Hale  125 1451     \n"
    "                                                       2013/04/02  125 1451     \n"
    "                                                                   125 1451     \n"
    "MF=33, MT=2 and 102 were replaced by the fine energy grid data,    125 1451     \n"
    "which were obtained from the R-matrix analysis at LANL.            125 1451     \n"
    "The description below for the ENDF/B-VII.1 covariance data         125 1451     \n"
    "was inconsistent with what we had in the 2011 release.             125 1451     \n"
    "Ref.[1] describes these fine-grid data, while the ENDF/B-VII.1     125 1451     \n"
    "covariance data, which were taken from the COMMARA-2.0 library,    125 1451     \n"
    "are an earlier coarse energy grid evaluation. The estimated        125 1451     \n"
    "uncertainties (point-wise, not binned) in the elastic (MT=2)       125 1451     \n"
    "and capture (MT=102) cross sections are:                           125 1451     \n"
    "                                                                   125 1451     \n"
    "     E[MeV] elastic[%] capture[%]                                  125 1451     \n"
    "       0.0    0.13       1.1                                       125 1451     \n"
    "       0.1    0.20       5.1                                       125 1451     \n"
    "       0.5    0.39       9.8                                       125 1451     \n"
    "       1      0.54      11                                         125 1451     \n"
    "       2      0.73      10                                         125 1451     \n"
    "       4      0.93       9.9                                       125 1451     \n"
    "       6      1.0        9.3                                       125 1451     \n"
    "       8      1.0        8.9                                       125 1451     \n"
    "      10      0.97       8.4                                       125 1451     \n"
    "      12      0.84       8.0                                       125 1451     \n"
    "      14      0.66       7.7                                       125 1451     \n"
    "      16      0.43       7.4                                       125 1451     \n"
    "      18      0.16       7.2                                       125 1451     \n"
    "      20      0.17       7.0                                       125 1451     \n"
    "                                                                   125 1451     \n"
    "REFERENCES                                                         125 1451     \n"
    "[1] G. M. Hale, \"Covariances from light-element R-matrix           125 1451     \n"
    "    analyses,\" Nuclear Data Sheets, 109, 2812 (2008).              125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "The new R-matrix analysis of the N-N system on which the ENDF/B-   125 1451     \n"
    "VII evaluation for 1H is based differs from the previous one use   125 1451     \n"
    "for ENDF/B-VI in several respects. Firstly, the n-p capture        125 1451     \n"
    "reaction (MT=102), and its inverse, deuteron photo-                125 1451     \n"
    "disintegration, were a part of the analysis, rather than added     125 1451     \n"
    "later as before. The analysis used a new method for including      125 1451     \n"
    "photon channels in R-matrix theory [1], which gave a better        125 1451     \n"
    "description of the E1 transitions, in particular.  The data for    125 1451     \n"
    "these reactions are mostly integrated and differential cross       125 1451     \n"
    "sections, but some information about polarizations was also        125 1451     \n"
    "included.  The thermal capture cross section was taken to be       125 1451     \n"
    "332.0 mb, as was the recommendation from preliminary data          125 1451     \n"
    "testing. Good agreement was obtained with recent cross-section     125 1451     \n"
    "measurements [2,3] by astrophysical groups in the 20-550 keV       125 1451     \n"
    "range, as well as with earlier measurements that had been done     125 1451     \n"
    "mostly as photo-disintegration experiments at energies below 14    125 1451     \n"
    "MeV.                                                               125 1451     \n"
    "The new analysis includes several additional measurements of the   125 1451     \n"
    "total cross section (MT=1).  The evaluated cross section           125 1451     \n"
    "deviates at most by about -0.5% around 10 MeV from that of         125 1451     \n"
    "ENDF/B-VI.                                                         125 1451     \n"
    "For n-p scattering (MT=2), new information was included about the  125 1451     \n"
    "low-energy cross sections (MF=3) and about the angular             125 1451     \n"
    "distributions (MF=4).  A new measurement of the angular            125 1451     \n"
    "distribution at 10 MeV [4], plus corrections to earlier data at    125 1451     \n"
    "14 MeV, moved the back-angle asymmetry in the 10-14 MeV range to   125 1451     \n"
    "values that lie between those obtained for ENDF/B-V and ENDF/B-    125 1451     \n"
    "VI.  The addition of the latest value of the thermal coherent      125 1451     \n"
    "scattering length [5] had the interesting effect of reducing the   125 1451     \n"
    "\"zero-energy\" scattering cross section somewhat to agree           125 1451     \n"
    "perfectly with an earlier measurement by Houk [6], and disagree    125 1451     \n"
    "with the later, more precise, value of Dilg [7].  The              125 1451     \n"
    "covariances for MT=2 will be added later, but the uncertainties    125 1451     \n"
    "on the integrated cross section should be similar to those         125 1451     \n"
    "listed above for the total cross section.                          125 1451     \n"
    "                                                                   125 1451     \n"
    "                                                                   125 1451     \n"
    "REFERENCES                                                         125 1451     \n"
    "                                                                   125 1451     \n"
    "[1] G. M. Hale and A. S. Johnson, Proc. 17th Int. IUPAP Conf. on   125 1451     \n"
    "    Few-Body Problems in Physics, 5-10 June 2003, Durham NC, W.    125 1451     \n"
    "    Gloeckle and W. Tornow,  eds., Elsevier B.V., pp. S120-S122    125 1451     \n"
    "   (2004).                                                         125 1451     \n"
    "[2] T. S. Suzuki et al., Astrophys. Lett. 449, L59 (1995).         125 1451     \n"
    "[3] Y. Nagai et al., Phys. Rev. C 56, 3173 (1997).                 125 1451     \n"
    "[4] N. Boukharouba et al., Phys. Rev. C 65, 014004 (2002).         125 1451     \n"
    "[5] K. Schoen et al., Phys. Rev. C 67, 044005 (2003).              125 1451     \n"
    "[6] T. L. Houk, Phys. Rev. C 3, 1886 (1971).                       125 1451     \n"
    "[7] W. Dilg, Phys. Rev. C 11, 103 (1975).                          125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                                                   125 1451     \n"
    "Covariances were adopted from COMMARA-2.0 library in July 2011.    125 1451     \n"
    "These covariances were obtained at LANL by full scale R-matrix     125 1451     \n"
    "analysis of more than 5000 experimental data (chi-square/degree    125 1451     \n"
    "of freedom of 0.83). [1] The major channel in this case is elastic 125 1451     \n"
    "scattering, often labeled also as ''n-p'' scattering. Elastic      125 1451     \n"
    "scattering serves as neutron cross section standard from 1 keV to  125 1451     \n"
    "20 MeV, with cross sections well determined. Uncertainties for     125 1451     \n"
    "elastic scattering rise from values well below 1%, reach maximum   125 1451     \n"
    "at about 8 MeV, then gradually decrease with increasing energy.    125 1451     \n"
    "In addition to elastic scattering, covariances are supplied for    125 1451     \n"
    "radiative capture.                                                 125 1451     \n"
    "                                                                   125 1451     \n"
    "REFERENCES                                                         125 1451     \n"
    "[1] G. M. Hale, \"Covariances from light-element R-matrix           125 1451     \n"
    "analyses,\" Nuclear Data Sheets, 109, 2812 (2008).                  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451        122          5 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1         35          4 125 1451     \n"
    "                                3          2         35          4 125 1451     \n"
    "                                3        102         35          5 125 1451     \n"
    "                                4          2        196          4 125 1451     \n"
    "                                6        102        201          4 125 1451     \n"
    "                               33          1          5          5 125 1451     \n"
    "                               33          2        779          5 125 1451     \n"
    "                               33        102        779          5 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n";
}

std::string chunk451() {
  return
    " 3.908800+4 8.715432+1          0          0          0          03988 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          63988 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          03988 1451     \n"
    " 2.936000+2 0.000000+0          1          0          6          23988 1451     \n"
    " 39- Y- 88 LANL                                                   3988 1451     \n"
    "LANL                                                              3988 1451     \n"
    "----LANL/RC-III       MATERIAL 3988                               3988 1451     \n"
    "-----INCIDENT NEUTRON DATA                                        3988 1451     \n"
    "------ENDF-6 FORMAT                                               3988 1451     \n"
    "***************************************************               3988 1451     \n"
    "                                1        451         12          03988 1451     \n"
    "                                3          1          4          03988 1451     \n"
    "                                                                  3988 1  0     \n";
}

void verifyChunk451( const file::Type< 1 >& chunk ) {

  CHECK( 1 == chunk.MF() );
  CHECK( 1 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 451 ) );
  CHECK( not chunk.hasMT( 4 ) );
  CHECK( chunk.hasSection( 451 ) );
  CHECK( not chunk.hasSection( 4 ) );

  CHECK_NOTHROW( chunk.MT( 451_c ) );
  CHECK_NOTHROW( chunk.section( 451_c ) );

  CHECK( 39088. == Approx( chunk.MT( 451_c ).ZA() ) );
  CHECK( 6 == chunk.MT( 451_c ).NWD() );
  CHECK( 2 == chunk.MT( 451_c ).NXC() );
  CHECK( 12 == chunk.MT( 451_c ).NC() );
}

std::string validSEND() {
  return
    "                                                                  3988 3  0     \n";
}

std::string validFEND() {
  return
    "                                                                  3988 0  0     \n";
}

std::string validMEND() {
  return
    "                                                                     0 0  0     \n";
}

std::string validTEND() {
  return
    "                                                                    -1 0  0     \n";
}

std::string validHEAD() {
  return
    " 3.908800+4 8.715432+1          0          0          0          03988 1451     \n";
}
