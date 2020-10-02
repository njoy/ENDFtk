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
    WHEN( "a valid TEND record ends the Tape" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = validTEND();
      auto tapeString = tpid + base + tend;

      syntaxTree::Tape< std::string > tape{ njoy::utility::copy( tapeString ) };

      syntaxTree::Tape< std::string > original{
        njoy::utility::copy( tapeString ) };

      THEN( "the copy and move ctor will function correctly ") {

        auto copy = syntaxTree::Tape< std::string >{ original };
        CHECK( 125 == copy.MAT( 125 ).front().MAT() );

        auto move = syntaxTree::Tape< std::string >{ std::move( copy ) };
        CHECK( 125 == move.MAT( 125 ).front().MAT() );
      }

      GIVEN("a tape skeleton constructed from a string"){
        syntaxTree::Tape< std::string > reference(
          njoy::utility::copy( tapeString ) );

        THEN("the iterator-based factory function will return the same type"){
          std::string copy = njoy::utility::copy( tapeString );
          auto trial = syntaxTree::makeTape( std::move( copy ) );
          constexpr bool isSame =
            std::is_same<decltype(reference), decltype(trial)>::value;
          CHECK( isSame );
        }

        THEN("the range-based factory function will return the same type"){
          auto trial = syntaxTree::makeTape(
              njoy::utility::copy( tapeString ) );
          constexpr bool isSame =
            std::is_same<decltype(reference), decltype(trial)>::value;
          CHECK( isSame );
        }
      }

      syntaxTree::Tape< std::string > tapeTree{
        njoy::utility::copy( tapeString ) };
      const auto ctapeTree = tapeTree;

      THEN( "the correct number of materials are read from the tape" ){
         CHECK( 1 == tapeTree.size() );
         CHECK( 1 == ctapeTree.size() );
      }

      AND_THEN( "we can access the Materials of the skeleton" ){
        CHECK( tapeTree.hasMaterialNumber( 125 ) );
        CHECK( ctapeTree.hasMaterialNumber( 125 ) );
        for ( auto& materialSkeleton : tapeTree.materialNumber( 125 ) ){
          CHECK( 125 == materialSkeleton.materialNumber() );
        }
        for ( const auto& materialSkeleton : ctapeTree.materialNumber( 125 ) ){
          CHECK( 125 == materialSkeleton.materialNumber() );
        }

        CHECK( tapeTree.hasMAT( 125 ) );
        CHECK( ctapeTree.hasMAT( 125 ) );
        for ( auto& materialSkeleton : tapeTree.MAT( 125 ) ){
          CHECK( 125 == materialSkeleton.materialNumber() );
        }
        for ( const auto& materialSkeleton : ctapeTree.MAT( 125 ) ){
          CHECK( 125 == materialSkeleton.materialNumber() );
        }
      }

      AND_THEN( "an excpetion is thrown for an invalid index" ){
        CHECK_THROWS( tapeTree.materialNumber(1) );
      }
    }


    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = invalidTEND();
      auto tapeString = tpid + base + tend;

      CHECK_THROWS( syntaxTree::Tape< std::string >{ std::move( tapeString ) } );
    }

    WHEN( "the Tape isn't long enough" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tapeString = tpid + base; // no tend record

      CHECK_THROWS( syntaxTree::Tape< std::string >{ std::move( tapeString ) } );
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
