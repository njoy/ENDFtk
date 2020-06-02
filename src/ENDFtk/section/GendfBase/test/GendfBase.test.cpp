#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


std::string validFEND();
std::string mfd3mt2();
std::string validSEND();
std::string invalidSEND();


SCENARIO( "creating a GendfBase object" ) {
  GIVEN( "a string representation of a GendfSection" ) {
    WHEN( "a valid section is given" ) {

      // MFD3, one temp, one sig0, one Legendre
      std::string buffer = mfd3mt2();

      auto begin = buffer.begin();
      auto end = buffer.end();
      long lineNo = 0;
      int MAT = 9228;
      HeadRecord head(begin, end, lineNo);

      THEN( "the object can be created" ) {
        section::GendfBase section(head, begin, end, lineNo, MAT );

        // head record parameter getters
        CHECK( section.legendreOrder() == 0 );
        CHECK( section.numLegendre() == 1 );
        CHECK( section.numSigma0() == 1 );
        CHECK( section.breakupFlag() == 0 );
        CHECK( section.numGroups() == 44 );

        // check temperature
        CHECK( section.temperature() == Approx(293.6) );

        // check lists
        CHECK( section.dataRecords().at(1).group() == 1 );
        CHECK( section.dataRecords().at(44).group() == 44 );

      }
    }
  }
}


std::string validFEND() {
  return
    "                                                                  9228 0  0    0\n";
}

std::string mfd3mt2() {
  return
    " 9.223500+4 0.000000+0          1          1          0         449228 3  2    1\n"
    " 2.936000+2 0.000000+0          2          1          2          19228 3  2    2\n"
    " 8.864840+4 1.469141+1                                            9228 3  2    3\n"
    " 2.936000+2 0.000000+0          2          1          2          29228 3  2    4\n"
    " 4.076628+5 1.430320+1                                            9228 3  2    5\n"
    " 2.936000+2 0.000000+0          2          1          2          39228 3  2    6\n"
    " 3.325475+5 1.422934+1                                            9228 3  2    7\n"
    " 2.936000+2 0.000000+0          2          1          2          49228 3  2    8\n"
    " 2.704187+6 1.415084+1                                            9228 3  2    9\n"
    " 2.936000+2 0.000000+0          2          1          2          59228 3  2   10\n"
    " 9.182484+5 1.409805+1                                            9228 3  2   11\n"
    " 2.936000+2 0.000000+0          2          1          2          69228 3  2   12\n"
    " 1.831983+6 1.406694+1                                            9228 3  2   13\n"
    " 2.936000+2 0.000000+0          2          1          2          79228 3  2   14\n"
    " 1.611269+6 1.402843+1                                            9228 3  2   15\n"
    " 2.936000+2 0.000000+0          2          1          2          89228 3  2   16\n"
    " 2.150369+6 1.397806+1                                            9228 3  2   17\n"
    " 2.936000+2 0.000000+0          2          1          2          99228 3  2   18\n"
    " 1.677811+6 1.389651+1                                            9228 3  2   19\n"
    " 2.936000+2 0.000000+0          2          1          2         109228 3  2   20\n"
    " 9.702871+5 1.378522+1                                            9228 3  2   21\n"
    " 2.936000+2 0.000000+0          2          1          2         119228 3  2   22\n"
    " 3.285728+5 1.362093+1                                            9228 3  2   23\n"
    " 2.936000+2 0.000000+0          2          1          2         129228 3  2   24\n"
    " 1.348773+5 1.352095+1                                            9228 3  2   25\n"
    " 2.936000+2 0.000000+0          2          1          2         139228 3  2   26\n"
    " 1.208261+5 1.348035+1                                            9228 3  2   27\n"
    " 2.936000+2 0.000000+0          2          1          2         149228 3  2   28\n"
    " 1.094424+5 1.347708+1                                            9228 3  2   29\n"
    " 2.936000+2 0.000000+0          2          1          2         159228 3  2   30\n"
    " 1.921488+5 1.352816+1                                            9228 3  2   31\n"
    " 2.936000+2 0.000000+0          2          1          2         169228 3  2   32\n"
    " 8.537350+4 1.355762+1                                            9228 3  2   33\n"
    " 2.936000+2 0.000000+0          2          1          2         179228 3  2   34\n"
    " 7.955453+4 1.353933+1                                            9228 3  2   35\n"
    " 2.936000+2 0.000000+0          2          1          2         189228 3  2   36\n"
    " 7.448245+4 1.350431+1                                            9228 3  2   37\n"
    " 2.936000+2 0.000000+0          2          1          2         199228 3  2   38\n"
    " 5.152778+5 1.330950+1                                            9228 3  2   39\n"
    " 2.936000+2 0.000000+0          2          1          2         209228 3  2   40\n"
    " 5.421450+5 1.289614+1                                            9228 3  2   41\n"
    " 2.936000+2 0.000000+0          2          1          2         219228 3  2   42\n"
    " 6.582378+5 1.263968+1                                            9228 3  2   43\n"
    " 2.936000+2 0.000000+0          2          1          2         229228 3  2   44\n"
    " 6.085370+5 1.195173+1                                            9228 3  2   45\n"
    " 2.936000+2 0.000000+0          2          1          2         239228 3  2   46\n"
    " 5.304027+5 1.137018+1                                            9228 3  2   47\n"
    " 2.936000+2 0.000000+0          2          1          2         249228 3  2   48\n"
    " 2.698745+5 1.075633+1                                            9228 3  2   49\n"
    " 2.936000+2 0.000000+0          2          1          2         259228 3  2   50\n"
    " 3.469132+5 1.070006+1                                            9228 3  2   51\n"
    " 2.936000+2 0.000000+0          2          1          2         269228 3  2   52\n"
    " 2.436662+5 1.161760+1                                            9228 3  2   53\n"
    " 2.936000+2 0.000000+0          2          1          2         279228 3  2   54\n"
    " 1.269261+6 1.149129+1                                            9228 3  2   55\n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3  2   56\n"
    " 1.389867+6 1.140790+1                                            9228 3  2   57\n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3  2   58\n"
    " 1.966742+6 1.152955+1                                            9228 3  2   59\n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3  2   60\n"
    " 1.958830+6 1.215428+1                                            9228 3  2   61\n"
    " 2.936000+2 0.000000+0          2          1          2         319228 3  2   62\n"
    " 2.003216+6 1.195243+1                                            9228 3  2   63\n"
    " 2.936000+2 0.000000+0          2          1          2         329228 3  2   64\n"
    " 4.448512+5 1.144792+1                                            9228 3  2   65\n"
    " 2.936000+2 0.000000+0          2          1          2         339228 3  2   66\n"
    " 1.600971+6 1.069586+1                                            9228 3  2   67\n"
    " 2.936000+2 0.000000+0          2          1          2         349228 3  2   68\n"
    " 1.653127+6 8.151080+0                                            9228 3  2   69\n"
    " 2.936000+2 0.000000+0          2          1          2         359228 3  2   70\n"
    " 1.607887+6 5.004643+0                                            9228 3  2   71\n"
    " 2.936000+2 0.000000+0          2          1          2         369228 3  2   72\n"
    " 1.044185+6 3.748074+0                                            9228 3  2   73\n"
    " 2.936000+2 0.000000+0          2          1          2         379228 3  2   74\n"
    " 5.807999+5 3.589833+0                                            9228 3  2   75\n"
    " 2.936000+2 0.000000+0          2          1          2         389228 3  2   76\n"
    " 4.118760+5 3.848525+0                                            9228 3  2   77\n"
    " 2.936000+2 0.000000+0          2          1          2         399228 3  2   78\n"
    " 7.543025+4 4.091297+0                                            9228 3  2   79\n"
    " 2.936000+2 0.000000+0          2          1          2         409228 3  2   80\n"
    " 2.347697+5 4.284081+0                                            9228 3  2   81\n"
    " 2.936000+2 0.000000+0          2          1          2         419228 3  2   82\n"
    " 3.334087+5 4.525173+0                                            9228 3  2   83\n"
    " 2.936000+2 0.000000+0          2          1          2         429228 3  2   84\n"
    " 8.667041+4 4.115439+0                                            9228 3  2   85\n"
    " 2.936000+2 0.000000+0          2          1          2         439228 3  2   86\n"
    " 3.704342+4 3.442857+0                                            9228 3  2   87\n"
    " 2.936000+2 0.000000+0          2          1          2         449228 3  2   88\n"
    " 1.292703+5 2.786681+0                                            9228 3  2   89\n"
    "                                                                  9228 3  099999\n";
}

std::string validSEND() {
  return
    "                                                                  9228 1  0    0\n";
}

std::string invalidSEND() {
  return
    "                                                                  9228 1451    0\n";
}


