#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


std::string getSection();


SCENARIO( "creating a GendfBase object" ) {
  GIVEN( "a string representation of a GendfSection" ) {
    WHEN( "a valid section is given" ) {

      std::string buffer = getSection();

      auto begin = buffer.begin();
      auto end = buffer.end();
      long lineNo = 0;
      int MAT = 9237;
      HeadRecord head(begin, end, lineNo);

      THEN( "the object can be created" ) {
        section::GendfType<3> chunk(head, begin, end, lineNo, MAT );

        // head record parameter getters
        CHECK( chunk.legendreOrder() == 1 );
        CHECK( chunk.numLegendre() == 2 );
        CHECK( chunk.numSigma0() == 2 );
        CHECK( chunk.breakupFlag() == 0 );
        CHECK( chunk.numGroups() == 10 );

        // check temperature
        CHECK( chunk.temperature() == Approx(293.6) );

        // check data
        CHECK( chunk.getCrossSection(1) == 0.0 );
        CHECK( chunk.getCrossSection(10) == Approx(10.46994) );
        CHECK( chunk.getCrossSection(2, 1, 0) == Approx(15.18365) );
        CHECK( chunk.getCrossSection(2, 0, 1) == Approx(15.17064) );
        CHECK_THROWS( chunk.getCrossSection(1, 3, 0) );
        CHECK_THROWS( chunk.getCrossSection(1, 0, 3) );
        CHECK_THROWS( chunk.getCrossSection(0) );

      }
    }
  }
}


std::string getSection() {
  return
    " 9.223800+4 0.000000+0          2          2          0         109237 3  1    1\n"
    " 2.936000+2 0.000000+0          2          1          8          29237 3  1    5\n"
    " 4.076628+5 4.076628+5 2.707485+5 1.798684+5 1.518365+1 1.518365+19237 3  1    6\n"
    " 1.517064+1 1.515778+1                                            9237 3  1    7\n"
    " 2.936000+2 0.000000+0          2          1          8          39237 3  1    8\n"
    " 3.325475+5 3.325475+5 2.276034+5 1.557802+5 1.383334+1 1.383334+19237 3  1    9\n"
    " 1.383249+1 1.383164+1                                            9237 3  1   10\n"
    " 2.936000+2 0.000000+0          2          1          8          49237 3  1   11\n"
    " 2.704187+6 2.704187+6 1.908900+6 1.347643+6 1.250311+1 1.250311+19237 3  1   12\n"
    " 1.249862+1 1.249418+1                                            9237 3  1   13\n"
    " 2.936000+2 0.000000+0          2          1          8          59237 3  1   14\n"
    " 9.182484+5 9.182484+5 6.589042+5 4.728086+5 1.180808+1 1.180808+19237 3  1   15\n"
    " 1.180798+1 1.180788+1                                            9237 3  1   16\n"
    " 2.936000+2 0.000000+0          2          1          8          69237 3  1   17\n"
    " 1.831983+6 1.831983+6 1.323545+6 9.562210+5 1.152468+1 1.152468+19237 3  1   18\n"
    " 1.152446+1 1.152423+1                                            9237 3  1   19\n"
    " 2.936000+2 0.000000+0          2          1          8          79237 3  1   20\n"
    " 1.611270+6 1.611270+6 1.171801+6 8.521988+5 1.125120+1 1.125120+19237 3  1   21\n"
    " 1.125110+1 1.125099+1                                            9237 3  1   22\n"
    " 2.936000+2 0.000000+0          2          1          8          89237 3  1   23\n"
    " 2.150370+6 2.150370+6 1.573657+6 1.151619+6 1.099457+1 1.099457+19237 3  1   24\n"
    " 1.099439+1 1.099421+1                                            9237 3  1   25\n"
    " 2.936000+2 0.000000+0          2          1          8          99237 3  1   26\n"
    " 1.677811+6 1.677811+6 1.236346+6 9.110428+5 1.071231+1 1.071231+19237 3  1   27\n"
    " 1.071217+1 1.071202+1                                            9237 3  1   28\n"
    " 2.936000+2 0.000000+0          2          1          8         109237 3  1   29\n"
    " 9.702869+5 9.702869+5 7.192670+5 5.331894+5 1.046994+1 1.046994+19237 3  1   30\n"
    " 1.046982+1 1.046969+1                                            9237 3  1   31\n"
    "                                                                  9237 3  099999\n";

}
