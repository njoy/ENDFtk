#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string baseTAPE();
std::string tpidString();
std::string validTEND();
std::string invalidTEND();

SCENARIO( "Creating a tape Skeleton of an ENDF File" ){
  GIVEN( "a string representation of a Tape" ){
    WHEN( "a valid TEND record ends the Tape"){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = validTEND();
      auto tapeString = tpid + base + tend;
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      syntaxTree::Tape< std::string::iterator > tapeTree( begin, end );
        
      THEN( "the buffer iterators are populated correctly "){
        REQUIRE( tapeString.begin() == tapeTree.buffer().begin() );
        REQUIRE( tapeString.end() == tapeTree.buffer().end() );
      }

      AND_THEN( "the correct number of materials are read from the tape" ){
         REQUIRE( 1 == tapeTree.size() );
      }
      
      AND_THEN( "we can access the Materials of the skeleton" ){
        REQUIRE( tapeTree.hasMaterialNumber( 125 ) );
        for ( auto& materialSkeleton : tapeTree.materialNumber( 125 ) ){
          REQUIRE( 125 == materialSkeleton.materialNumber() );
        }

        REQUIRE( tapeTree.hasMAT( 125 ) );
        for ( auto& materialSkeleton : tapeTree.MAT( 125 ) ){
          REQUIRE( 125 == materialSkeleton.materialNumber() );
        }
      }
      AND_THEN( "an excpetion is thrown for an invalid index" ){
        REQUIRE_THROWS( tapeTree.materialNumber(1) );
      }
    }

    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = invalidTEND();
      auto tapeString = tpid + base + tend;
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      REQUIRE_THROWS( syntaxTree::Tape< std::string::iterator >( begin, end ) );
    }

    WHEN( "the Tape isn't long enough" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tapeString = tpid + base; // no tend record
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      REQUIRE_THROWS( syntaxTree::Tape< std::string::iterator >( begin, end ) );
    }
  } // GIVEN
} // SCENARIO

const std::string& cachedTape(){
  const static std::string tape =
    njoy::utility::slurpFileToMemory( "n-001_H_001.endf" );
  return tape;
}

std::string tpidString(){
  return std::string( cachedTape().begin(),
                      std::next( cachedTape().begin(), 76 ) );
}

std::string baseTAPE(){
  auto begin = std::next( cachedTape().begin(), 76 );
  auto end =
    std::next( std::make_reverse_iterator( cachedTape().end() ), 76 ).base();
  return std::string( begin, end );
}

std::string validTEND(){
  auto begin =
    std::next( std::make_reverse_iterator( cachedTape().end() ), 76 ).base();
  auto end = cachedTape().end();
  return std::string( begin, end );
}

std::string invalidTEND(){
  auto TEND = validTEND();
  TEND.at(69) = '2';
  return TEND;
}
