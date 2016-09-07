#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace ENDFtk::implementation;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "File Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "File Complete!";
  return result;
}

