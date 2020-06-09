#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


std::string sampleSection();
std::string validMEND();
std::string validFEND();
std::string validSEND();
std::string invalidSEND();


SCENARIO( "testing creation of GENDF material object" ) {
  GIVEN( "a string representation of a GendfMaterial" ) {
    WHEN( "a valid material is given" ){

      // MFD1, MT451 uses FEND rather than SEND
      std::string buffer = sampleSection() + validFEND() + validMEND();

      auto begin = buffer.begin();
      auto position = begin;
      auto end = buffer.end();
      long lineNo = 0;

      // construct object
      HeadRecord head( position, end, lineNo );
      syntaxTree::GendfMaterial< std::string::iterator >
          matl( head, begin, position, end, lineNo );

      THEN( "the whole stream is read" ) {
        CHECK( lineNo == 14 );
      }
      AND_THEN( "one section is found" ) {
        CHECK( matl.size() == 1 );
        CHECK( matl.hasSection(1, 451) );
        CHECK( not matl.hasSection(3, 1) );
        CHECK( matl.MAT() == 9228 );
        CHECK( matl.materialNumber() == 9228 );
      }
      AND_THEN( "the object is iterable" ) {
        for ( auto& section : matl )
          CHECK( section.MT() == 451 );
      }

    }
  }
}

std::string sampleSection() {
  return
    " 9.223500+4 2.330248+2          0          1         -1          19228 1451    1\n"
    " 2.936000+2 0.000000+0         44         12         60          09228 1451    2\n"
    " 0.000000+0 1.00000+10 1.000000-5 3.000000-3 7.500000-3 1.000000-29228 1451    3\n"
    " 2.530000-2 3.000000-2 4.000000-2 5.000000-2 7.000000-2 1.000000-19228 1451    4\n"
    " 1.500000-1 2.000000-1 2.250000-1 2.500000-1 2.750000-1 3.250000-19228 1451    5\n"
    " 3.500000-1 3.750000-1 4.000000-1 6.250000-1 1.000000+0 1.770000+09228 1451    6\n"
    " 3.000000+0 4.750000+0 6.000000+0 8.100000+0 1.000000+1 3.000000+19228 1451    7\n"
    " 1.000000+2 5.500000+2 3.000000+3 1.700000+4 2.500000+4 1.000000+59228 1451    8\n"
    " 4.000000+5 9.000000+5 1.400000+6 1.850000+6 2.354000+6 2.479000+69228 1451    9\n"
    " 3.000000+6 4.800000+6 6.434000+6 8.187300+6 2.000000+7 1.000000+49228 1451   10\n"
    " 1.000000+5 5.000000+5 1.000000+6 2.000000+6 3.000000+6 4.000000+69228 1451   11\n"
    " 5.000000+6 6.000000+6 7.000000+6 8.000000+6 9.000000+6 2.000000+79228 1451   12\n";
}

std::string validMEND() {
  return
    "                                                                     0 0  0    0\n";
}

std::string validFEND() {
  return
    "                                                                  9228 0  0    0\n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0    0\n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 1451    0\n";
}


