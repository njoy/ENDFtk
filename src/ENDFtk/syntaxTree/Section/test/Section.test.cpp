#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

std::string baseSection();
std::string validSEND();
std::string invalidSEND();

using namespace njoy::ENDFtk;

SCENARIO( "Creating a syntax tree of an ENDF Section" ){
  GIVEN( "A string representation of a Section" ){
    WHEN( "a valid SEND record ends the Section" ){
      std::string sectionString = baseSection() + validSEND();
      auto position = sectionString.begin();
      auto start = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      syntaxTree::Section< std::string::iterator >
        sectionTree( head, start, position, end, lineNumber );

      const auto& csectionTree = sectionTree;
      
      THEN( "the entire stream is read" ){
        REQUIRE( 36 == lineNumber );
      }

      AND_THEN( "the buffer iterators are populated correctly "){
        REQUIRE( sectionString.begin() == sectionTree.buffer().begin() );
        REQUIRE( end == sectionTree.buffer().end() );
        REQUIRE( sectionString.begin() == csectionTree.buffer().begin() );
        REQUIRE( end == csectionTree.buffer().end() );
      }

      AND_THEN( "the file/section number or MF/MT is populated correctly" ){
        REQUIRE( 3 == sectionTree.MF() );
        REQUIRE( 3 == sectionTree.fileNumber() );
        REQUIRE( 1 == sectionTree.MT() );
        REQUIRE( 1 == sectionTree.sectionNumber() );
        REQUIRE( 1 == csectionTree.MT() );
        REQUIRE( 1 == csectionTree.sectionNumber() );
      }

      AND_THEN( "the first record of the section is a head record" ){
        auto start = sectionTree.buffer().begin();
        auto end = sectionTree.buffer().end();
        long lineNumber = 0;

        HeadRecord head( start, end, lineNumber );
        REQUIRE( head.ZA() == 1.001E3 );
        REQUIRE( head.AWR() == 9.991673E-1 );
        REQUIRE( head.L1() == 0 );
        REQUIRE( head.L2() == 0 );
        REQUIRE( head.N1() == 0 );
        REQUIRE( head.N2() == 0 );
      }
    } // WHEN

    WHEN( "an invalid (MT!=0) SEND record ends the Section" ){
      std::string sectionString = baseSection() + invalidSEND();
      THEN( "an exception is thrown" ){
        auto begin = sectionString.begin();
        auto start = sectionString.begin();
        auto end = sectionString.end();
        long lineNumber = 0;

        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS( syntaxTree::Section< std::string::iterator >( 
                head, start, begin, end, lineNumber ) );
      }
    } // WHEN
    
    WHEN( "a Section that is too short (no SEND record)" ){
      THEN( "an exception is thrown" ){
        std::string sectionString = baseSection();
        auto begin = sectionString.begin();
        auto start = sectionString.begin();
        auto end = sectionString.end();
        long lineNumber = 0;
        HeadRecord head( begin, end, lineNumber );
        REQUIRE_THROWS( syntaxTree::Section< std::string::iterator >(
                head, start, begin, end, lineNumber ) );
      }
    }
  } // GIVEN
} // SCENARIO

std::string baseSection(){
  return
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1\n"
    " 0.000000+0 0.000000+0          0          0          2         96 125 3  1\n"
    "         30          5         96          2                       125 3  1\n"
    " 1.000000-5 3.713628+1 2.000000-5 3.224498+1 5.000000-5 2.790478+1 125 3  1\n"
    " 1.000000-4 2.571732+1 2.000000-4 2.417056+1 5.000000-4 2.279806+1 125 3  1\n"
    " 1.000000-3 2.210633+1 2.000000-3 2.161720+1 5.000000-3 2.118318+1 125 3  1\n"
    " 1.000000-2 2.096443+1 2.530000-2 2.076834+1 5.000000-2 2.067250+1 125 3  1\n"
    " 1.000000-1 2.060332+1 2.000000-1 2.055439+1 5.000000-1 2.051095+1 125 3  1\n"
    " 1.000000+0 2.048901+1 2.000000+0 2.047341+1 5.000000+0 2.045928+1 125 3  1\n"
    " 1.000000+1 2.045169+1 2.000000+1 2.044545+1 5.000000+1 2.043707+1 125 3  1\n"
    " 1.000000+2 2.042815+1 2.000000+2 2.041317+1 5.000000+2 2.037161+1 125 3  1\n"
    " 1.000000+3 2.030435+1 2.000000+3 2.017221+1 4.000000+3 1.991433+1 125 3  1\n"
    " 6.000000+3 1.966407+1 8.000000+3 1.942096+1 1.000000+4 1.918468+1 125 3  1\n"
    " 1.500000+4 1.862195+1 2.000000+4 1.809600+1 4.000000+4 1.629575+1 125 3  1\n"
    " 6.000000+4 1.486744+1 8.000000+4 1.370595+1 1.000000+5 1.274239+1 125 3  1\n"
    " 1.500000+5 1.092347+1 2.000000+5 9.643237+0 3.000000+5 7.951994+0 125 3  1\n"
    " 4.000000+5 6.876451+0 5.000000+5 6.125481+0 6.000000+5 5.566913+0 125 3  1\n"
    " 7.000000+5 5.132043+0 8.000000+5 4.781603+0 9.000000+5 4.491504+0 125 3  1\n"
    " 1.000000+6 4.246138+0 1.200000+6 3.850489+0 1.400000+6 3.541783+0 125 3  1\n"
    " 1.600000+6 3.291349+0 1.800000+6 3.082224+0 2.000000+6 2.903682+0 125 3  1\n"
    " 2.200000+6 2.748580+0 2.400000+6 2.611955+0 2.600000+6 2.490235+0 125 3  1\n"
    " 2.800000+6 2.380773+0 3.000000+6 2.281558+0 3.200000+6 2.191030+0 125 3  1\n"
    " 3.400000+6 2.107954+0 3.600000+6 2.031337+0 3.800000+6 1.960371+0 125 3  1\n"
    " 4.000000+6 1.894386+0 4.200000+6 1.832823+0 4.400000+6 1.775213+0 125 3  1\n"
    " 4.600000+6 1.721153+0 4.800000+6 1.670299+0 5.000000+6 1.622354+0 125 3  1\n"
    " 5.500000+6 1.513587+0 6.000000+6 1.418191+0 6.500000+6 1.333743+0 125 3  1\n"
    " 7.000000+6 1.258400+0 7.500000+6 1.190730+0 8.000000+6 1.129596+0 125 3  1\n"
    " 8.500000+6 1.074084+0 9.000000+6 1.023447+0 9.500000+6 9.770666-1 125 3  1\n"
    " 1.000000+7 9.344290-1 1.050000+7 8.950999-1 1.100000+7 8.587108-1 125 3  1\n"
    " 1.150000+7 8.249463-1 1.200000+7 7.935351-1 1.250000+7 7.642418-1 125 3  1\n"
    " 1.300000+7 7.368615-1 1.350000+7 7.112148-1 1.400000+7 6.871439-1 125 3  1\n"
    " 1.450000+7 6.645095-1 1.500000+7 6.431880-1 1.550000+7 6.230693-1 125 3  1\n"
    " 1.600000+7 6.040552-1 1.650000+7 5.860577-1 1.700000+7 5.689977-1 125 3  1\n"
    " 1.750000+7 5.528040-1 1.800000+7 5.374121-1 1.850000+7 5.227637-1 125 3  1\n"
    " 1.900000+7 5.088059-1 1.950000+7 4.954905-1 2.000000+7 4.827735-1 125 3  1\n";
}

std::string validSEND(){
  return
    "                                                                   125 3  0\n";
}

std::string invalidSEND(){
  return
    "                                                                   125 3  1\n";
}
