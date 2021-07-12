#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/tree/Tape.hpp"

// other includes
#include "header-utilities/copy.hpp"
#include "header-utilities/slurpFileToMemory.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::string baseTAPE();
std::string tpidString();
std::string validTEND();
std::string invalidTEND();

SCENARIO( "tree::Tape" ) {

  GIVEN( "an empty tree::Tape" ) {

    WHEN( "it is created" ) {

      tree::Tape tape( TapeIdentification( "this is my tape identification" ) );

      THEN( "it is empty except for the tape ID" ) {

        auto numbers = tape.materialNumbers();
        CHECK( 0 == tape.size() );
        CHECK( 0 == numbers.size() );

        CHECK( "this is my tape identification                                       0 0  0     \n"
               "                                                                    -1 0  0     \n" == tape.content() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a string representation of a Tape" ){
    WHEN( "a valid TEND record ends the Tape" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = validTEND();
      auto tapeString = tpid + base + tend;

      tree::Tape tape{ njoy::utility::copy( tapeString ) };

      tree::Tape original{ njoy::utility::copy( tapeString ) };

      THEN( "the copy and move ctor will function correctly ") {

        auto copy = tree::Tape{ original };
        CHECK( 125 == copy.MAT( 125 ).front().MAT() );

        auto move = tree::Tape{ std::move( copy ) };
        CHECK( 125 == move.MAT( 125 ).front().MAT() );
      }

      GIVEN("a tape skeleton constructed from a string"){
        tree::Tape reference(
          njoy::utility::copy( tapeString ) );

        THEN("the iterator-based factory function will return the same type"){
          std::string copy = njoy::utility::copy( tapeString );
          auto trial = tree::Tape( std::move( copy ) );
          constexpr bool isSame =
            std::is_same<decltype(reference), decltype(trial)>::value;
          CHECK( isSame );
        }

        THEN("the range-based factory function will return the same type"){
          auto trial = tree::Tape(
              njoy::utility::copy( tapeString ) );
          constexpr bool isSame =
            std::is_same<decltype(reference), decltype(trial)>::value;
          CHECK( isSame );
        }
      }

      tree::Tape tapeTree{
        njoy::utility::copy( tapeString ) };
      const auto ctapeTree = tapeTree;

      THEN( "the correct number of materials are read from the tape" ){
         CHECK( 1 == tapeTree.size() );
         CHECK( 1 == ctapeTree.size() );
      }

      AND_THEN( "we can access the Materials of the skeleton" ){
        CHECK( tapeTree.hasMaterial( 125 ) );
        CHECK( ctapeTree.hasMaterial( 125 ) );
        for ( auto& materialSkeleton : tapeTree.material( 125 ) ){
          CHECK( 125 == materialSkeleton.materialNumber() );
        }
        for ( const auto& materialSkeleton : ctapeTree.material( 125 ) ){
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
        CHECK_THROWS( tapeTree.material(1) );
      }
    }


    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tend = invalidTEND();
      auto tapeString = tpid + base + tend;

      CHECK_THROWS( tree::Tape{ std::move( tapeString ) } );
    }

    WHEN( "the Tape isn't long enough" ){
      auto tpid = tpidString();
      auto base = baseTAPE();
      auto tapeString = tpid + base; // no tend record

      CHECK_THROWS( tree::Tape{ std::move( tapeString ) } );
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
