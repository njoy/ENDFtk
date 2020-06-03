#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;


std::string singleDilutionSingleLegendre();
std::string multipleDilutionSingleLegendre();
std::string multipleDilutionMultipleLegendre();


SCENARIO( "creating a GendfBase object" ) {
  GIVEN( "a string representation of a GendfSection" ) {
    WHEN( "a valid section is given with single dilution/Legendre" ) {

      std::string buffer = singleDilutionSingleLegendre();

      auto begin = buffer.begin();
      auto end = buffer.end();
      long lineNo = 0;
      int MAT = 9231;
      HeadRecord head(begin, end, lineNo);

      THEN( "the object can be created" ) {
        section::GendfType<6> chunk(head, begin, end, lineNo, MAT );

        // head record parameter getters
        CHECK( chunk.legendreOrder() == 0 );
        CHECK( chunk.numLegendre() == 1 );
        CHECK( chunk.numSigma0() == 1 );
        CHECK( chunk.breakupFlag() == 0 );
        CHECK( chunk.numGroups() == 4 );

        // check temperature
        CHECK( chunk.temperature() == Approx(293.6) );

        // check data
        CHECK( chunk.getMatrixElement(1, 1) == 0.0 );
        CHECK( chunk.getMatrixElement(4, 4) == Approx(0.5641136) );
        CHECK( chunk.getMatrixElement(4, 3) == Approx(0.001889547) );
        CHECK( chunk.getMatrixElement(4, 1, 0, 0) == 0.0 );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 3, 0) );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 0, 3) );
        CHECK_THROWS( chunk.getMatrixElement(1, 0, 0, 0) );
        CHECK_THROWS( chunk.getMatrixElement(0, 1, 0, 0) );
      }
    }

    WHEN( "the section has multiple dilutions/single Legendre" ) {

      std::string buffer = multipleDilutionSingleLegendre();

      auto begin = buffer.begin();
      auto end = buffer.end();
      long lineNo = 0;
      int MAT = 9231;
      HeadRecord head(begin, end, lineNo);

      THEN( "the object can be created" ) {
        section::GendfType<6> chunk(head, begin, end, lineNo, MAT );

        // head record parameter getters
        CHECK( chunk.legendreOrder() == 0 );
        CHECK( chunk.numLegendre() == 1 );
        CHECK( chunk.numSigma0() == 2 );
        CHECK( chunk.breakupFlag() == 0 );
        CHECK( chunk.numGroups() == 4 );

        // check temperature
        CHECK( chunk.temperature() == Approx(293.6) );

        // check data
        CHECK( chunk.getMatrixElement(1, 1) == Approx(13.08591) );
        CHECK( chunk.getMatrixElement(4, 4, 0, 1) == Approx(6.795481) );
        CHECK( chunk.getMatrixElement(4, 3) == Approx(0.01691256) );
        CHECK( chunk.getMatrixElement(4, 1, 0, 0) == 0.0 );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 3, 0) );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 0, 3) );
        CHECK_THROWS( chunk.getMatrixElement(1, 0, 0, 0) );
        CHECK_THROWS( chunk.getMatrixElement(0, 1, 0, 0) );
      }
    }

    WHEN( "the section has multiple dilutions/Legendres" ) {

      std::string buffer = multipleDilutionMultipleLegendre();

      auto begin = buffer.begin();
      auto pos = begin;
      auto end = buffer.end();
      long lineNo = 0;
      int MAT = 9231;
      HeadRecord head(pos, end, lineNo);

      THEN( "the object can be created from a syntaxTree" ) {
        syntaxTree::GendfSection< std::string::iterator >
          tree(head, begin, pos, end, lineNo);
        auto chunk = tree.parse<6>();

        // head record parameter getters
        CHECK( chunk.legendreOrder() == 2 );
        CHECK( chunk.numLegendre() == 3 );
        CHECK( chunk.numSigma0() == 2 );
        CHECK( chunk.breakupFlag() == 0 );
        CHECK( chunk.numGroups() == 4 );

        // check temperature
        CHECK( chunk.temperature() == Approx(293.6) );

        // check data
        CHECK( chunk.getMatrixElement(1, 1) == Approx(13.08591) );
        CHECK( chunk.getMatrixElement(4, 4, 0, 1) == Approx(6.795481) );
        CHECK( chunk.getMatrixElement(4, 3, 2, 1) == Approx(-1.461486e-6) );
        CHECK( chunk.getMatrixElement(4, 1, 0, 0) == 0.0 );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 3, 0) );
        CHECK_THROWS( chunk.getMatrixElement(1, 1, 0, 3) );
        CHECK_THROWS( chunk.getMatrixElement(1, 0, 0, 0) );
        CHECK_THROWS( chunk.getMatrixElement(0, 1, 0, 0) );
      }
    }
  }
}


std::string multipleDilutionSingleLegendre() {
  return
    " 9.223600+4 0.000000+0          1          2          0          49231 6  2    1\n"
    " 2.936000+2 0.000000+0          2          1          4          19231 6  2    2\n"
    " 7.836093+0 2.066847-1 1.308591+1 9.964397+0                      9231 6  2    3\n"
    " 2.936000+2 0.000000+0          3          1          6          29231 6  2    4\n"
    " 5.063323+0 4.380571-1 1.488054-2 1.146178-2 8.538194+0 8.513820+09231 6  2    5\n"
    " 2.936000+2 0.000000+0          3          2          6          39231 6  2    6\n"
    " 7.824099+0 5.997011-1 6.905855-3 8.003645-3 2.515695+1 1.074624+19231 6  2    7\n"
    " 2.936000+2 0.000000+0          3          3          6          49231 6  2    8\n"
    " 7.601016+0 7.489501-1 1.691256-2 1.003045-2 8.111733+0 6.795481+09231 6  2    9\n"
    "                                                                  9231 6  099999\n";
}

std::string multipleDilutionMultipleLegendre() {
  return
    " 9.223600+4 0.000000+0          3          2          0          49231 6  2    1\n"
    " 2.936000+2 0.000000+0          2          1         12          19231 6  2    2\n"
    " 7.836093+0 7.836093+0 7.836093+0 2.066847-1 8.373871-3 4.064310-49231 6  2    3\n"
    " 1.308591+1 3.727915-2 4.841787-5 9.964397+0 2.603868-2 3.313675-59231 6  2    4\n"
    " 2.936000+2 0.000000+0          3          1         18          29231 6  2    5\n"
    " 5.063323+0 5.063323+0 5.063323+0 4.380571-1 3.832580-2 3.387609-39231 6  2    6\n"
    " 1.488054-2-4.932024-3-1.692182-5 1.146178-2-2.896314-3-5.591585-69231 6  2    7\n"
    " 8.538194+0 2.929976-2 4.856660-5 8.513820+0 2.710764-2 3.693604-59231 6  2    8\n"
    " 2.936000+2 0.000000+0          3          2         18          39231 6  2    9\n"
    " 7.824099+0 7.824099+0 7.824099+0 5.997011-1 5.604142-2 6.268131-39231 6  2   10\n"
    " 6.905855-3-2.280570-3-1.283959-5 8.003645-3-2.497460-3-2.209360-59231 6  2   11\n"
    " 2.515695+1 8.592875-2 4.188720-3 1.074624+1 3.278044-2 8.844580-49231 6  2   12\n"
    " 2.936000+2 0.000000+0          3          3         18          49231 6  2   13\n"
    " 7.601016+0 7.601016+0 7.601016+0 7.489501-1 8.041605-2 9.253031-39231 6  2   14\n"
    " 1.691252-2-5.565639-3-1.212732-5 1.003043-2-1.797672-3-1.461486-69231 6  2   15\n"
    " 8.111733+0 1.767513+0 1.134979+0 6.795481+0 2.207837+0 1.721833+09231 6  2   16\n"
    "                                                                  9231 6  099999\n";
}

std::string singleDilutionSingleLegendre() {
  return
    " 9.223600+4 0.000000+0          1          1          0          49231 6 51    1\n"
    " 2.936000+2 0.000000+0          4          2          4          49231 6 51    2\n"
    " 7.601016+0 3.96073-10 1.889547-3 5.641136-1                      9231 6 51    3\n"
    "                                                                  9231 6  099999\n";
}
