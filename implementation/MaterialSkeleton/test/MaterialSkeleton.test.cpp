#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "utility.hpp"

#include "ENDFtk.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "MaterialSkeleton Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "MaterialSkeleton Complete!";
  return result;
}

using namespace ENDFtk::implementation;

std::string baseMaterial();
std::string validMEND();
std::string invalidMEND();

SCENARIO( "Creating a material Skeleton of an ENDF File" ){
  GIVEN( "a string representation of a Material" ){
    WHEN( "a valid MEND record ends the Material" ){
      THEN("head can be constructed"){
        std::string materialString = baseMaterial() + validMEND();
        auto begin = materialString.begin();
        auto end = materialString.end();
        long lineNumber = 0;
        REQUIRE_NOTHROW
          ( HeadRecord( begin, end, lineNumber ) );      
      }

      THEN("material can be constructed"){
        std::string materialString = baseMaterial() + validMEND();
        auto begin = materialString.begin();
        auto start = begin;
        auto end = materialString.end();
        long lineNumber = 0;
        HeadRecord head( begin, end, lineNumber );
        REQUIRE_NOTHROW
          ( MaterialSkeleton< std::string::iterator >
            ( head, start, begin, end, lineNumber ) );
      }
      
      std::string materialString = baseMaterial() + validMEND();
      auto begin = materialString.begin();
      auto start = begin;
      auto end = materialString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );
      MaterialSkeleton< std::string::iterator >
        materialSkeleton( head, start, begin, end, lineNumber );
      
      THEN( "the entire stream is read" ){
        REQUIRE( 2208 == lineNumber );
      }

      AND_THEN( "the buffer iterators are populated correctly "){
        REQUIRE( materialString.begin() == materialSkeleton.bufferBegin() );
        REQUIRE( materialString.end() == materialSkeleton.bufferEnd() );
      }

      AND_THEN( "the material number or MAT is populated correctly" ){
        REQUIRE( 125 == materialSkeleton.MAT() );
      }
      
      AND_THEN( "the correct number of files are read from the material" ){
        REQUIRE( 6 == materialSkeleton.size() );
      }

      AND_THEN( "we can access the file skeletons of the skeleton" ){
        std::vector< int > fileNumbers{ 1, 2, 3, 4, 6, 33 };
        for ( auto fileNo : fileNumbers ){
          REQUIRE( materialSkeleton.hasMF( fileNo ) );
          REQUIRE( fileNo == materialSkeleton.MF( fileNo ).MF() );
          REQUIRE( materialSkeleton.hasFileNumber( fileNo ) );
          REQUIRE( fileNo == materialSkeleton.fileNumber( fileNo ).MF() );
        }
        
        auto fileNumberIterator = fileNumbers.begin();

        for( auto& fileSkeleton : materialSkeleton ){
          REQUIRE( *fileNumberIterator == fileSkeleton.MF() );
          ++fileNumberIterator;
        }
      }

      AND_THEN( "an exception is thrown if the requested MF isn't stored."){
        REQUIRE_THROWS( materialSkeleton.MF( 5 ) );
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
          ( MaterialSkeleton< std::string::iterator >
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
          ( MaterialSkeleton< std::string::iterator >
            ( head, start, begin, end, lineNumber ) );
      }
    }
  } // GIVEN

  WHEN( "a material has more than one file with the same number" ){
    std::string materialString = baseMaterial() + baseMaterial() + validMEND();
    auto begin = materialString.begin();
    auto start = materialString.begin();
    auto end = materialString.end();
    long lineNumber = 0;
    
    THEN( "an exception is thrown" ){
      HeadRecord head( begin, end, lineNumber );
      REQUIRE_THROWS
        ( MaterialSkeleton< std::string::iterator >
          ( head, start, begin, end, lineNumber ) );
    }
  }
} // SCENARIO

std::string baseMaterial(){
  static std::string materialString =
    utility::slurpFileToMemory( "./n-001_H_001.endf" );
  auto materialBegin = std::next( materialString.begin(), 76 );
  auto materialEnd =
    std::next( std::make_reverse_iterator( materialString.end() ), 152 ).base();
  return std::string( materialBegin, materialEnd );
}

std::string validMEND(){
  return 
    "                                                                     0 0  0\n";
}

std::string invalidMEND(){
  return
    "                                                                   125 0  0\n";
}
