#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "ENDFtk/implementation/RecordTail.hpp"

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "RecordTail Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "RecordTail Tests Complete!";
  return result;
}
