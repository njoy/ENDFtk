#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string getFile( int MF );
std::string chunk457();
void verifyChunk457( const file::Type< 8 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();
std::string validHEAD();

SCENARIO( "Testing special case of file 8" ) {

  GIVEN( "valid data for a File 8" ) {

    WHEN( "a file::Type< 8 > is constructed using only mt457" ) {

      section::Type< 8, 457 >
      mt457( // zaid, awr, lis, liso
             95242., 239.9801, 2, 1,
             // decay energies
             { {{ 4.449622e+9, 6.311520e+7 }}, 
               { {{ 4.008322e+4, 4.128931e+3 }},
                 {{ 5.373671e+3, 3.660206e+2 }},
                 {{ 2.441003e+4, 6.191754e+2 }} } },
             // decay modes
             { 5., -1.,
               { { 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 },
               { 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 },
               { 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 } } },
             // spectra
             { { 0.0, {{ 1., 0. }}, {{ 2.107044e+2, 1.576284e+1 }},
                 { { 3., {{ 4.863000e+4, 5.000000e+1 }},
                   {{ 1.420112e-6, 2.85306e-10 }}, 0.0,
                   {{ 0.0, 0.0 }}, {{ 7.010000e+5, 1.106180e-2 }}, {{ 0.0, 0.0 }},
                   {{ 3.315735e+5, 5.608008e+3 }} },
                 { 4., {{ 4.935000e+4, 2.000000e+1 }},
                   {{ 1.335690e-3, 5.409179e-5 }}, 0.0,
                   {{ 0.0, 0.0 }}, {{ 8.209999e-1, 0.000000e+0 }}, {{ 0.0, 0.0 }},
                   {{ 6.160000e-1, 8.999999e-3 }} } } },
               { 1.0, {{ 0.5, 0.25 }}, {{ 3.107044e+2, 4.576284e+1 }},
                 { 4., { 3 }, { 1 }, { 0.0, 5e+5, 7.3e+6 },
                   { 6.133200e-7, 6.133300e-7, 6.02040e-17 } } } });

      file::Type< 8 > mf8( std::move( mt457 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk457( mf8 );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf8.print( output, 3580 );

        CHECK( buffer == chunk457() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 8 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      std::string string = chunk457() + validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 8 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      std::string string = chunk457() + validMEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 8 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      std::string string = chunk457() + validTEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 8 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a HEAD instead of FEND" ) {

      std::string string = chunk457() + validHEAD();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 8 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string fileString = getFile( 8 );

  GIVEN( "a string representation of of File 8" ) {

    WHEN( "a file::Type< 8 > is constructed from the string" ) {

      auto begin = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 8 > file( division, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        CHECK( file.hasMT( 457 ) );
        CHECK( not file.hasMT( 1 ) );
        CHECK( file.hasSection( 457 ) );
        CHECK( not file.hasSection( 1 ) );

        CHECK( 92235. == Approx( file.section( 457_c ).ZA() ) );
        CHECK( 92235. == Approx( file.MT( 457_c ).ZA() ) );
      }
    }

    WHEN( "a file::Type< 8 > is constructed from a syntaxTree" ) {

      auto begin = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string::iterator >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 8 > can be constructed" ) {

        CHECK_NOTHROW( fileTree.parse< 8 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 8 > is constructed from the string twice" ) {

      std::string twice( fileString.begin(), fileString.end() - 81 );
      twice += fileString;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 8 >( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 8 >" ) {

    auto begin = fileString.begin();
    auto end = fileString.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 8 > file( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      file.print( output, 3515 );
      CHECK( buffer == fileString );
    }
  } // GIVEN
} // SCENARIO

std::string getFile( int MF ){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "dec-092_U_235.endf" );
  syntaxTree::Tape< std::string > tapeTree( njoy::utility::copy( tape ) );
  auto fileTree = tapeTree.materialNumber( 3515 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

std::string chunk457() {
  return
    " 9.524200+4 2.399801+2          2          1          0          23580 8457     \n"
    " 4.449622+9 6.311520+7          0          0          6          03580 8457     \n"
    " 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n"
    " 5.000000+0-1.000000+0          0          0         18          33580 8457     \n"
    " 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n"
    " 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n"
    " 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n"
    " 0.000000+0 0.000000+0          0          0          6          23580 8457     \n"
    " 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n"
    " 4.863000+4 5.000000+1          0          0         12          03580 8457     \n"
    " 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n"
    " 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n"
    " 4.935000+4 2.000000+1          0          0         12          03580 8457     \n"
    " 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n"
    " 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n"
    " 0.000000+0 1.000000+0          1          0          6          03580 8457     \n"
    " 0.000000+0 0.000000+0 3.107044+2 4.576284+1 5.000000-1 2.500000-13580 8457     \n"
    " 4.000000+0 0.000000+0          0          0          1          33580 8457     \n"
    "          3          1                                            3580 8457     \n"
    " 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n"
    "                                                                  3580 8  0     \n";
}

void verifyChunk457( const file::Type< 8 >& chunk ) {

  CHECK( 8 == chunk.MF() );
  CHECK( 8 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 457 ) );
  CHECK( not chunk.hasMT( 1 ) );
  CHECK( chunk.hasSection( 457 ) );
  CHECK( not chunk.hasSection( 1 ) );

  CHECK_NOTHROW( chunk.MT( 457_c ) );
  CHECK_NOTHROW( chunk.section( 457_c ) );

  CHECK( 95242. == Approx( chunk.MT( 457_c ).ZA() ) );
  CHECK( 2 == chunk.MT( 457_c ).LIS() );
  CHECK( 1 == chunk.MT( 457_c ).LISO() );
  CHECK( 20 == chunk.MT( 457_c ).NC() );
}

std::string validSEND() {
  return
    "                                                                  3580 8  0     \n";
}

std::string validFEND() {
  return
    "                                                                  3580 0  0     \n";
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
    " 9.524200+4 2.399801+2          2          1          0          23580 8457     \n";
}

