#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "utility.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "TapeSkeleton Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "TapeSkeleton Complete!";
  return result;
}

using namespace ENDFtk::implementation;

std::string baseTAPE();
std::string tpidString();
std::string validTEND();
std::string invalidTEND();

SCENARIO( "Creating a tape Skeleton of an ENDF File" ){
  GIVEN( "a string representation of a Tape" ){
    WHEN( "a valid TEND record ends the Tape"){

      auto tapeString = tpidString() + baseTAPE() + validTEND();
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      TapeSkeleton< std::string::iterator > tapeSkeleton( begin, end );
        
      THEN( "the buffer iterators are populated correctly "){
        REQUIRE( tapeString.begin() == tapeSkeleton.bufferBegin() );
        REQUIRE( tapeString.end() == tapeSkeleton.bufferEnd() );
      }

      AND_THEN( "the correct number of materials are read from the tape" ){
         REQUIRE( 1 == tapeSkeleton.size() );
      }
      
      AND_THEN( "we can access the Materials of the skeleton" ){
        REQUIRE( tapeSkeleton.hasMaterialNumber( 125 ) );
        REQUIRE( 1 == tapeSkeleton.materialNumber( 125 ).size() );
        for ( auto& materialSkeleton : tapeSkeleton.materialNumber( 125 ) ){
          REQUIRE( 125 == materialSkeleton.materialNumber() );
        }

        REQUIRE_THROWS( tapeSkeleton.materialNumber( 125 ).at(1) );

        REQUIRE( tapeSkeleton.hasMAT( 125 ) );
        for ( auto& materialSkeleton : tapeSkeleton.MAT( 125 ) ){
          REQUIRE( 125 == materialSkeleton.materialNumber() );
        }
      }
      AND_THEN( "an excpetion is thrown for an invalid index" ){
        REQUIRE_THROWS( tapeSkeleton.materialNumber(1) );
      }
    }

    WHEN( "an invalid (MAT != -1) TEND record ends the Tape" ){
      auto tapeString = tpidString() + baseTAPE() + invalidTEND();
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      REQUIRE_THROWS( TapeSkeleton< std::string::iterator >( begin, end ) );
    }

    WHEN( "the Tape isn't long enough" ){
      auto tapeString = tpidString() + baseTAPE(); // no tend record
      auto begin = tapeString.begin();
      auto end = tapeString.end();

      REQUIRE_THROWS( TapeSkeleton< std::string::iterator >( begin, end ) );
    }
  } // GIVEN
} // SCENARIO

const std::string& cachedTape(){
  const static std::string tape =
    utility::slurpFileToMemory( "n-001_H_001.endf" );
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
  TEND[69] = '2';
  return TEND;
}
