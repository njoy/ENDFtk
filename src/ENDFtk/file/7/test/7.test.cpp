#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/file/7.hpp"

// other includes
#include "ENDFtk/tree/File.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using TabulatedFunctions = section::Type< 7, 4 >::TabulatedFunctions;
using ScatteringFunction = section::Type< 7, 4 >::TabulatedFunctions::ScatteringFunction;

std::string chunk7();
std::string chunk2();
void verifyChunk2( const file::Type< 7 >& );
std::string chunk4();
void verifyChunk4( const file::Type< 7 >& );
std::string chunk24();
void verifyChunk24( const file::Type< 7 >& );
std::string validSEND();
std::string validFEND();
std::string validMEND();
std::string validTEND();
std::string validHEAD();

// TODO find another MF7 file without numbers < 1e-35

SCENARIO( "Testing special case of file 7" ) {

  GIVEN( "valid data for a File 7" ) {

    WHEN( "a file::Type<7> is constructed using only mt2" ) {

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

        CHECK_THROWS( mf7.MT( 4_c ) );
        CHECK_THROWS( mf7.section( 4_c ) );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        CHECK( buffer == chunk2() + validFEND() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<7> is constructed using only mt4" ) {

      section::Type< 7, 4 >
      mt4( 127., 8.934780e+0, 1, 0,
           { 0, 1.976285e+2, 5.000001e+0,
             6.153875e+0, 8.934780e+0, 1 },
           TabulatedFunctions(
                      { 2 }, { 4 },
                      { ScatteringFunction(
                                   293.6, 0.0, { 5 }, { 4 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                     1.306574e-9, 5.29573e-10 } ),
                        ScatteringFunction(
                                   293.6, 3.952570e-2, { 5 }, { 2 },
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

        CHECK_THROWS( mf7.MT( 2_c ) );
        CHECK_THROWS( mf7.section( 2_c ) );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        CHECK( buffer == chunk4() + validFEND() );
      } // THEN
    } // WHEN

    WHEN( "a file::Type<7> is constructed using an mt2 and and mt4" ) {

      section::Type< 7, 2 >
      mt2( 127., 1.,
           CoherentElastic( 293.6, { 3 }, { 1 },
                            { 1.059427e-3, 3.718355e-3,  4.237708e-3 },
                            { 0.0, 9.364524e-3, 1.548925e-2 } ) );

      section::Type< 7, 4 >
      mt4( 127., 8.934780e+0, 1, 0,
           { 0, 1.976285e+2, 5.000001e+0,
             6.153875e+0, 8.934780e+0, 1 },
           TabulatedFunctions(
                      { 2 }, { 4 },
                      { ScatteringFunction(
                                   293.6, 0.0, { 5 }, { 4 },
                                   { 4.423802e-3, 4.649528e-3, 4.886772e-3,
                                     8.418068e+1, 8.847604e+1 },
                                   { 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                     1.306574e-9, 5.29573e-10 } ),
                        ScatteringFunction(
                                   293.6, 3.952570e-2, { 5 }, { 2 },
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

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        mf7.print( output, 27 );

        CHECK( buffer == chunk24() + validFEND() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of File 7 with errors in the END records" ) {

    WHEN( "there is a SEND instead of FEND" ) {

      std::string string = chunk24() + validSEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 7 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a MEND instead of FEND" ) {

      std::string string = chunk24() + validMEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 7 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a TEND instead of FEND" ) {

      std::string string = chunk24() + validTEND();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 7 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN

    WHEN( "there is a HEAD instead of FEND" ) {

      std::string string = chunk24() + validHEAD();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( file::Type< 7 >( division, begin, end, lineNumber ) );
      } // THEN
    } // WHEN
  } // GIVEN

  std::string fileString = chunk7();

  GIVEN( "a string representation of of File 7" ) {

    WHEN( "a file::Type< 7 > is constructed from the string" ) {

      auto begin = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );
      file::Type< 7 > file( division, begin, end, lineNumber );

      THEN( "the sections can be extracted" ) {

        CHECK( file.hasMT( 2 ) );
        CHECK( file.hasMT( 4 ) );
        CHECK( not file.hasMT( 1 ) );
        CHECK( file.hasSection( 2 ) );
        CHECK( file.hasSection( 4 ) );
        CHECK( not file.hasSection( 1 ) );

        CHECK( 127. == Approx( file.section( 2_c ).ZA() ) );
        CHECK( 127. == Approx( file.MT( 2_c ).ZA() ) );

        CHECK( 127. == Approx( file.section( 4_c ).ZA() ) );
        CHECK( 127. == Approx( file.MT( 4_c ).ZA() ) );
      }
    }

    WHEN( "a file::Type< 7 > is constructed from a syntaxTree" ){
      auto begin = fileString.begin();
      auto start = fileString.begin();
      auto end = fileString.end();
      long lineNumber = 0;

      StructureDivision division( begin, end, lineNumber );

      tree::File file( asHead( division ), start, begin, end, lineNumber );

      THEN( "a file::Type< 7 > can be constructed" ){
        CHECK_NOTHROW( file.parse< 7 >( lineNumber ) );
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
        CHECK_THROWS( file::Type< 7 >
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
//      CHECK( buffer == fileString );
    }
  } // GIVEN
} // SCENARIO

std::string chunk7() {

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

std::string chunk2() {
  return
    " 1.270000+2 1.000000+0          1          0          0          0  27 7  2     \n"
    " 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n"
    "          3          1                                              27 7  2     \n"
    " 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n"
    "                                                                    27 7  0     \n";
}

void verifyChunk2( const file::Type< 7 >& chunk ) {

  CHECK( 7 == chunk.MF() );
  CHECK( 7 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 2 ) );
  CHECK( not chunk.hasMT( 4 ) );
  CHECK( chunk.hasSection( 2 ) );
  CHECK( not chunk.hasSection( 4 ) );

  CHECK_NOTHROW( chunk.MT( 2_c ) );
  CHECK_NOTHROW( chunk.section( 2_c ) );

  CHECK( 127. == Approx( chunk.MT( 2_c ).ZA() ) );
  CHECK( 1 == chunk.MT( 2_c ).LTHR() );
  CHECK( 4 == chunk.MT( 2_c ).NC() );
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
    "                                                                    27 7  0     \n";
}

void verifyChunk4( const file::Type< 7 >& chunk ) {

  CHECK( 7 == chunk.MF() );
  CHECK( 7 == chunk.fileNumber() );

  CHECK( not chunk.hasMT( 2 ) );
  CHECK( chunk.hasMT( 4 ) );
  CHECK( not chunk.hasSection( 2 ) );
  CHECK( chunk.hasSection( 4 ) );

  CHECK( not chunk.hasMT( 12 ) );
  CHECK( not chunk.hasSection( 12 ) );

  CHECK_NOTHROW( chunk.MT( 4_c ) );
  CHECK_NOTHROW( chunk.section( 4_c ) );

  CHECK( 127. == Approx( chunk.MT( 4_c ).ZA() ) );
  CHECK( 1 == chunk.MT( 4_c ).LAT() );
  CHECK( 0 == chunk.MT( 4_c ).LASYM() );

  CHECK( 16 == chunk.MT( 4_c ).NC() );
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
    "                                                                    27 7  0     \n";
}

void verifyChunk24( const file::Type< 7 >& chunk ) {

  CHECK( 7 == chunk.MF() );
  CHECK( 7 == chunk.fileNumber() );

  CHECK( chunk.hasMT( 2 ) );
  CHECK( chunk.hasMT( 4 ) );
  CHECK( chunk.hasSection( 2 ) );
  CHECK( chunk.hasSection( 4 ) );

  CHECK( not chunk.hasMT( 12 ) );
  CHECK( not chunk.hasSection( 12 ) );

  CHECK_NOTHROW( chunk.MT( 2_c ) );
  CHECK_NOTHROW( chunk.MT( 4_c ) );
  CHECK_NOTHROW( chunk.section( 2_c ) );
  CHECK_NOTHROW( chunk.section( 4_c ) );

  CHECK( 127. == Approx( chunk.MT( 2_c ).ZA() ) );
  CHECK( 1 == chunk.MT( 2_c ).LTHR() );
  CHECK( 4 == chunk.MT( 2_c ).NC() );

  CHECK( 127. == Approx( chunk.MT( 4_c ).ZA() ) );
  CHECK( 1 == chunk.MT( 4_c ).LAT() );
  CHECK( 0 == chunk.MT( 4_c ).LASYM() );
  CHECK( 16 == chunk.MT( 4_c ).NC() );
}

std::string validSEND() {
  return
    "                                                                    27 7  0     \n";
}

std::string validFEND() {
  return
    "                                                                    27 0  0     \n";
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
    " 1.270000+2 1.000000+0          1          0          0          0  27 7  2     \n";
}
