#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

std::string baseMaterial();
std::string validMEND();
std::string invalidMEND();

using namespace njoy::ENDFtk;

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
          < syntaxTree::Material< std::string::iterator > >
          ( head, start, beg, end, lin );
        
        THEN( "the copy ctor will function correctly "){
          auto copy = syntaxTree::Material< std::string::iterator >{ *original };
          original.reset();
          REQUIRE( 3 == copy.MF( 3 ).MF() );          
        }

        beg = begin;
        lin = lineNumber;
        original =
          std::make_unique
          < syntaxTree::Material< std::string::iterator > >
          ( head, start, beg, end, lin );

        THEN( "the move ctor will function correctly "){
          auto copy =
            syntaxTree::Material< std::string::iterator >
            { std::move( *( original.release() ) ) };
          
          REQUIRE( 3 == copy.MF( 3 ).MF() );          
        }
      }
      
      const syntaxTree::Material< std::string::iterator >
        materialTree( head, start, begin, end, lineNumber );

      const auto& cmaterialTree = materialTree;
      
      THEN( "the entire stream is read" ){
        REQUIRE( 2208 == lineNumber );
      }

      AND_THEN( "the buffer iterators are populated correctly "){
        REQUIRE( materialString.begin() == materialTree.buffer().begin() );
        REQUIRE( materialString.end() == materialTree.buffer().end() );
        REQUIRE( materialString.begin() == cmaterialTree.buffer().begin() );
        REQUIRE( materialString.end() == cmaterialTree.buffer().end() );
      }

      AND_THEN( "the material number or MAT is populated correctly" ){
        REQUIRE( 125 == materialTree.MAT() );
        REQUIRE( 125 == cmaterialTree.MAT() );
      }
      
      AND_THEN( "the correct number of files are read from the material" ){
        REQUIRE( 6 == materialTree.size() );
        REQUIRE( 6 == cmaterialTree.size() );
      }

      AND_THEN( "we can access the file skeletons of the skeleton" ){
        std::vector< int > fileNumbers{ 1, 2, 3, 4, 6, 33 };
        for ( auto fileNo : fileNumbers ){
          REQUIRE( materialTree.hasMF( fileNo ) );
          REQUIRE( fileNo == materialTree.MF( fileNo ).MF() );
          REQUIRE( materialTree.hasFileNumber( fileNo ) );
          REQUIRE( fileNo == materialTree.fileNumber( fileNo ).MF() );

          REQUIRE( cmaterialTree.hasMF( fileNo ) );
          REQUIRE( fileNo == cmaterialTree.MF( fileNo ).MF() );
          REQUIRE( cmaterialTree.hasFileNumber( fileNo ) );
          REQUIRE( fileNo == cmaterialTree.fileNumber( fileNo ).MF() );
        }
        
        auto fileNumberIterator = fileNumbers.begin();

        for( auto& file : materialTree ){
          REQUIRE( *fileNumberIterator == file.MF() );
          ++fileNumberIterator;
        }

        fileNumberIterator = fileNumbers.begin();

        for( const auto& file : cmaterialTree ){
          REQUIRE( *fileNumberIterator == file.MF() );
          ++fileNumberIterator;
        }
      }

      AND_THEN( "an exception is thrown if the requested MF isn't stored."){
        REQUIRE_THROWS( materialTree.MF( 5 ) );
        REQUIRE_THROWS( cmaterialTree.MF( 5 ) );
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
          ( syntaxTree::Material< std::string::iterator >
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
          ( syntaxTree::Material< std::string::iterator >
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
        ( syntaxTree::Material< std::string::iterator >
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
