#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using Tabulated = section::Type< 7, 4 >::Tabulated;
using BetaValue = section::Type< 7, 4 >::Tabulated::BetaValue;

std::string& cachedTape();
std::string getFile( int MF );
std::string chunk2();
void verifyChunk2( const file::Type< 7 >& );
std::string chunk4();
void verifyChunk4( const file::Type< 7 >& );
std::string chunk24();
void verifyChunk24( const file::Type< 7 >& );

// TODO fix ctor for MF7 so that the first test actually compiles
// TODO find another MF7 file without numbers < 1e-35

SCENARIO( "Testing special case of file 7" ) {

  GIVEN( "valid data for a File 7" ) {

    WHEN( "a file::Type<7> is constructed using only mf2" ) {

      section::Type< 7, 2 >
      mt2( 127., 1., 
           CoherentElastic( 293.6, { 3 }, { 1 },
                            { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                            { 0.0, 9.364524e-3, 1.548925e-2 } ) );

      file::Type< 7 > mf7( std::move( mt2 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk2( mf7 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        REQUIRE_THROWS( mf7.MT( 4_c ) );
        REQUIRE_THROWS( mf7.section( 4_c ) );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        REQUIRE( buffer == chunk2() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<7> is constructed using only mf4" ) {

      section::Type< 7, 4 >
      mt4( 127., 8.934780e+0, 1, 0,
           { 0, 1.976285e+2, 5.000001e+0,
             6.153875e+0, 8.934780e+0, 1 },
           Tabulated( { 2 }, { 4 },
                      { BetaValue( 293.6, 0.0, { 5 }, { 4 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3, 
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                     1.306574e-9, 5.29573e-10 } ),
                        BetaValue( 293.6, 3.952570e-2, { 5 }, { 2 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                     2.770291e-4, 2.911373e-4 } ) } ),
                      { { 3 }, { 2 }, 
                        { 293.6, 600., 1200. }, 
                        { 5.332083e+2, 7.354726e+2, 1.270678e+3 } } );

      file::Type< 7 > mf7( std::move( mt4 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk4( mf7 );
      } // THEN

      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        REQUIRE_THROWS( mf7.MT( 2_c ) );
        REQUIRE_THROWS( mf7.section( 2_c ) );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        REQUIRE( buffer == chunk4() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<7> is constructed using an mf2 and and mf4" ) {

      section::Type< 7, 2 >
      mt2( 127., 1., 
           CoherentElastic( 293.6, { 3 }, { 1 },
                            { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                            { 0.0, 9.364524e-3, 1.548925e-2 } ) );

      section::Type< 7, 4 >
      mt4( 127., 8.934780e+0, 1, 0,
           { 0, 1.976285e+2, 5.000001e+0,
             6.153875e+0, 8.934780e+0, 1 },
           Tabulated( { 2 }, { 4 },
                      { BetaValue( 293.6, 0.0, { 5 }, { 4 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3, 
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                     1.306574e-9, 5.29573e-10 } ),
                        BetaValue( 293.6, 3.952570e-2, { 5 }, { 2 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386694e-4, 2.508273e-4, 2.636238e-4,
                                     2.770291e-4, 2.911373e-4 } ) } ),
                      { { 3 }, { 2 }, 
                        { 293.6, 600., 1200. }, 
                        { 5.332083e+2, 7.354726e+2, 1.270678e+3 } } );

      file::Type< 7 > mf7( std::move( mt2 ), std::move( mt4 ) );

      THEN( "the sections can be extracted and interrogated" ) {

        verifyChunk24( mf7 );
      } // THEN

/*      THEN( "an exception is thrown if invalid MT or section is requested" ) {

        REQUIRE_THROWS( mf7.MT( 5_c ) );
        REQUIRE_THROWS( mf7.section( 5_c ) );
      } // THEN
*/
      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        REQUIRE( buffer == chunk24() );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string fileString = getFile( 7 );

  GIVEN( "a string representation of of File 7" ) {

    WHEN( "a file::Type< 7 > is constructed from the string" ) {

      auto begin = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 7 > file( division, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        REQUIRE( file.hasMT( 2 ) );
        REQUIRE( file.hasMT( 4 ) );
        REQUIRE( not file.hasMT( 1 ) );
        REQUIRE( file.hasSection( 2 ) );
        REQUIRE( file.hasSection( 4 ) );
        REQUIRE( not file.hasSection( 1 ) );

        REQUIRE( 127. == Approx( file.section( 2_c ).ZA() ) );
        REQUIRE( 127. == Approx( file.MT( 2_c ).ZA() ) );
      }
    }

    WHEN( "a file::Type< 7 > is constructed from a syntaxTree" ){
      auto begin = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      syntaxTree::File< std::string::iterator >
        fileTree( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 7 > can be constructed" ){
        REQUIRE_NOTHROW( fileTree.parse< 7 >( lineNumber ) );
      }
    }

    WHEN( "a file::Type< 7 > is constructed from the string twice" ){
      std::string twice( fileString.begin(), fileString.end() - 81 );
      twice += fileString;
      auto begin = twice.begin();
      auto end = twice.end();
      long lineNumber = 0;
      StructureDivision division( begin, end, lineNumber );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( file::Type< 7 >
                        ( division, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  GIVEN( "a valid instance of file::Type< 7 >" ) {
    auto begin = fileString.begin();
    auto end = fileString.end();
    long lineNumber = 0;

    StructureDivision division( begin, end, lineNumber );
    file::Type< 7 > file( division, begin, end, lineNumber );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      file.print( output, 27 );
//      REQUIRE( buffer == fileString );
    }
  } // GIVEN
} // SCENARIO

std::string& cachedTape(){
  static std::string tape =
    njoy::utility::slurpFileToMemory( "tsl-BeinBeO.endf" );
  return tape;
}

std::string getFile( int MF ){
  auto begin = cachedTape().begin();
  auto end = cachedTape().end();
  syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
  auto fileTree = tapeTree.materialNumber( 27 ).front().fileNumber( MF );
  return std::string( fileTree.buffer().begin(), fileTree.buffer().end() );
}

std::string chunk2() {
  return
    " 1.270000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    "                                                                    27 7  0     \n"
    "                                                                    27 0  0     \n";
}

void verifyChunk2( const file::Type< 7 >& chunk ) {

  REQUIRE( 7 == chunk.MF() );
  REQUIRE( 7 == chunk.fileNumber() );

  REQUIRE( chunk.hasMT( 2 ) );
  REQUIRE( not chunk.hasMT( 4 ) );
  REQUIRE( chunk.hasSection( 2 ) );
  REQUIRE( not chunk.hasSection( 4 ) );

  REQUIRE_NOTHROW( chunk.MT( 2_c ) );
  REQUIRE_THROWS( chunk.MT( 4_c ) );
  REQUIRE_NOTHROW( chunk.section( 2_c ) );
  REQUIRE_THROWS( chunk.section( 4_c ) );

  REQUIRE( 127. == Approx( chunk.MT( 2_c ).ZA() ) );
  REQUIRE( 1 == chunk.MT( 2_c ).LTHR() );
  REQUIRE( 4 == chunk.MT( 2_c ).NC() );
}

std::string chunk4() {
  return
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n"
    "                                                                    27 7  0     \n"
    "                                                                    27 0  0     \n";
}

void verifyChunk4( const file::Type< 7 >& chunk ) {

  REQUIRE( 7 == chunk.MF() );
  REQUIRE( 7 == chunk.fileNumber() );

  REQUIRE( not chunk.hasMT( 2 ) );
  REQUIRE( chunk.hasMT( 4 ) );
  REQUIRE( not chunk.hasSection( 2 ) );
  REQUIRE( chunk.hasSection( 4 ) );

  REQUIRE( not chunk.hasMT( 12 ) );
  REQUIRE( not chunk.hasSection( 12 ) );

  REQUIRE_THROWS( chunk.MT( 2_c ) );
  REQUIRE_NOTHROW( chunk.MT( 4_c ) );
  REQUIRE_THROWS( chunk.section( 2_c ) );
  REQUIRE_NOTHROW( chunk.section( 4_c ) );

  REQUIRE( 127. == Approx( chunk.MT( 4_c ).ZA() ) );
  REQUIRE( 1 == chunk.MT( 4_c ).LAT() );
  REQUIRE( 0 == chunk.MT( 4_c ).LASYM() );
  REQUIRE( 16 == chunk.MT( 4_c ).NC() );
}

std::string chunk24() {
  return
    " 1.270000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    "                                                                    27 7  0     \n"
    " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
    " 6.153875+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n"
    "          2          4                                              27 7  4     \n"
    " 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n"
    "          5          4                                              27 7  4     \n"
    " 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n"
    " 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n"
    "          5          2                                              27 7  4     \n"
    " 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n"
    " 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n"
    " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
    "          3          2                                              27 7  4     \n"
    " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n"
    "                                                                    27 7  0     \n"
    "                                                                    27 0  0     \n";
}

void verifyChunk24( const file::Type< 7 >& chunk ) {

  REQUIRE( 7 == chunk.MF() );
  REQUIRE( 7 == chunk.fileNumber() );

  REQUIRE( chunk.hasMT( 2 ) );
  REQUIRE( chunk.hasMT( 4 ) );
  REQUIRE( chunk.hasSection( 2 ) );
  REQUIRE( chunk.hasSection( 4 ) );

  REQUIRE( not chunk.hasMT( 12 ) );
  REQUIRE( not chunk.hasSection( 12 ) );

  REQUIRE_NOTHROW( chunk.MT( 2_c ) );
  REQUIRE_NOTHROW( chunk.MT( 4_c ) );
  REQUIRE_NOTHROW( chunk.section( 2_c ) );
  REQUIRE_NOTHROW( chunk.section( 4_c ) );

  REQUIRE( 127. == Approx( chunk.MT( 2_c ).ZA() ) );
  REQUIRE( 1 == chunk.MT( 2_c ).LTHR() );
  REQUIRE( 4 == chunk.MT( 2_c ).NC() );

  REQUIRE( 127. == Approx( chunk.MT( 4_c ).ZA() ) );
  REQUIRE( 1 == chunk.MT( 4_c ).LAT() );
  REQUIRE( 0 == chunk.MT( 4_c ).LASYM() );
  REQUIRE( 16 == chunk.MT( 4_c ).NC() );
}

