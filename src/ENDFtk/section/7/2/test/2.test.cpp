#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using ScatteringLaw = section::Type< 7, 2 >::ScatteringLaw;
using CoherentElastic = section::Type< 7, 2 >::CoherentElastic;
using IncoherentElastic = section::Type< 7, 2 >::IncoherentElastic;

std::string validSEND();
std::string invalidSEND();
std::string chunkWithCoherentElastic();
std::string chunkWithIncoherentElastic();
std::string chunkWithInvalidLTHR();

std::string chunkWithIncoherentElastic() {
  return
    " 1.070000+2 1.000000+0          2          0          0          0   7 7  2     \n"
    " 8.198006+1 0.000000+0          0          0          1          3   7 7  2     \n"
    "          3          2                                               7 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0   7 7  2     \n";
}

std::string chunkWithInvalidLTHR() {
  return
    " 1.070000+2 1.000000+0          3          0          0          0   7 7  2     \n"
    " 8.198006+1 0.000000+0          0          0          1          3   7 7  2     \n"
    "          3          2                                               7 7  2     \n"
    " 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0   7 7  2     \n";
}

std::string validSEND() {
  return
    "                                                                    27 7  0     \n";
}

std::string invalidSEND() {
  return
    "                                                                    27 7  4     \n";
}

