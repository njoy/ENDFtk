#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk/implementation/RecordTail.hpp"

std::unique_ptr<ENDFtk::implementation::RecordTail> myTail;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "RecordTail Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "RecordTail Tests Complete!";
  return result;
}

SCENARIO( "Checking the values of MAT, MF, and MT" ){
  GIVEN( "A string containing the MAT, MF, and MT of a Record" ){
    std::string tail(" 125 4  2");

    myTail = std::make_unique<
      ENDFtk::implementation::RecordTail>(125, 4, 2);

    THEN( "the correct values are read in" ){
      REQUIRE( 125 == myTail->MAT_ );
      REQUIRE(   4 == myTail->MF_  );
      REQUIRE(   2 == myTail->MT_  );
    }

  }
} // SCENARIO
