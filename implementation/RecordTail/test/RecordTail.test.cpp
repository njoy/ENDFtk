#define CATCH_CONFIG_RUNNER

#include <string>

#include "catch.hpp"

#include "ENDFtk/implementation/RecordTail.hpp"

std::unique_ptr<ENDFtk::implementation::RecordTail> myTail;
int mat = 125;
int mf = 4;
int mt = 2;

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
      ENDFtk::implementation::RecordTail>(mat, mf, mt);

    THEN( "the correct values are read in" ){
      REQUIRE( mat == myTail->MAT_ );
      REQUIRE(  mf == myTail->MF_  );
      REQUIRE(  mt == myTail->MT_  );
    }

  }
} // SCENARIO
