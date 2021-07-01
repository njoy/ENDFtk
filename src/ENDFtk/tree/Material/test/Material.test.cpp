#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

// other includes
#include "header-utilities/slurpFileToMemory.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string baseMaterial();
std::string validMEND();
std::string invalidMEND();

SCENARIO( "Creating a material syntax tree of an ENDF File" ){
  GIVEN( "a string representation of a Material" ){
    WHEN( "a valid MEND record ends the Material" ){
      std::string materialString = baseMaterial() + validMEND();
      auto begin = materialString.begin();
      auto start = begin;
      auto end = materialString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      GIVEN( "the Material pointer" ){
        auto beg = begin;
        auto lin = lineNumber;
        auto original =
          std::make_unique
          < tree::Material >
          ( head, start, beg, end, lin );

        THEN( "the copy ctor will function correctly "){
          auto copy = tree::Material{ *original };
          original.reset();
          REQUIRE( 3 == copy.MF( 3 ).MF() );
        }

        beg = begin;
        lin = lineNumber;
        original =
          std::make_unique
          < tree::Material >
          ( head, start, beg, end, lin );

        THEN( "the move ctor will function correctly "){
          auto copy =
            tree::Material
            { std::move( *( original.release() ) ) };

          REQUIRE( 3 == copy.MF( 3 ).MF() );
        }
      }

      const tree::Material material( head, start, begin, end, lineNumber );

      const auto& cmaterial = material;

      THEN( "the entire stream is read" ){
        REQUIRE( 2208 == lineNumber );
      }

      AND_THEN( "the material number or MAT is populated correctly" ){
        REQUIRE( 125 == material.MAT() );
        REQUIRE( 125 == cmaterial.MAT() );
      }

      AND_THEN( "the correct number of files are read from the material" ){
        REQUIRE( 6 == material.size() );
        REQUIRE( 6 == cmaterial.size() );
      }

      AND_THEN( "we can access the file skeletons of the skeleton" ){
        std::vector< int > fileNumbers{ 1, 2, 3, 4, 6, 33 };
        for ( auto fileNo : fileNumbers ){
          REQUIRE( material.hasMF( fileNo ) );
          REQUIRE( fileNo == material.MF( fileNo ).MF() );
          REQUIRE( material.hasFile( fileNo ) );
          REQUIRE( fileNo == material.file( fileNo ).MF() );

          REQUIRE( cmaterial.hasMF( fileNo ) );
          REQUIRE( fileNo == cmaterial.MF( fileNo ).MF() );
          REQUIRE( cmaterial.hasFile( fileNo ) );
          REQUIRE( fileNo == cmaterial.file( fileNo ).MF() );
        }

        auto fileNumberIterator = fileNumbers.begin();

        for( auto& file : material ){
          REQUIRE( *fileNumberIterator == file.MF() );
          ++fileNumberIterator;
        }

        fileNumberIterator = fileNumbers.begin();

        for( const auto& file : cmaterial ){
          REQUIRE( *fileNumberIterator == file.MF() );
          ++fileNumberIterator;
        }
      }

      AND_THEN( "an exception is thrown if the requested MF isn't stored."){
        REQUIRE_THROWS( material.MF( 5 ) );
        REQUIRE_THROWS( cmaterial.MF( 5 ) );
      }
    }

    WHEN( "an invalid (MAT != 0) MEND record ends the Material" ){
      std::string materialString = baseMaterial() + invalidMEND();
      THEN( "an exception is thrown" ){
        auto begin = materialString.begin();
        auto start = materialString.begin();
        auto end = materialString.end();
        long lineNumber = 0;

        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS
          ( tree::Material
            ( head, start, begin, end, lineNumber ) );
      }
    }

    WHEN( "a material is too short (no MEND record)" ){
      std::string materialString = baseMaterial();
      auto begin = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      THEN( "an exception is thrown" ){
        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS
          ( tree::Material
            ( head, start, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  WHEN( "a material has more than one file with the same number" ){
    std::string materialString = baseMaterial() + baseMaterial() + validMEND();
    auto begin = materialString.begin();
    auto start = begin;
    auto end = materialString.end();
    long lineNumber = 0;

    THEN( "an exception is thrown" ){
      HeadRecord head( begin, end, lineNumber );
      REQUIRE_THROWS
        ( tree::Material
          ( head, start, begin, end, lineNumber ) );
    }
  }
} // SCENARIO

const std::string& cachedTape(){
  static const std::string tape =
    njoy::utility::slurpFileToMemory( "./n-001_H_001.endf" );
  return tape;
}

std::string baseMaterial(){
  static const auto& tape = cachedTape();
  static const auto materialBegin = std::next( tape.begin(), 76 );
  static const auto materialEnd = tape.end() - 152;
  return std::string( materialBegin, materialEnd );
}

std::string validMEND(){
  static const auto& tape = cachedTape();
  static const auto MENDBegin = cachedTape().end() - 152;
  static const auto MENDEnd = std::next( MENDBegin, 76 );
  return std::string( MENDBegin, MENDEnd );
}

std::string invalidMEND(){
  auto MEND = validMEND();
  MEND.at(69) = '1';
  return MEND;
}
