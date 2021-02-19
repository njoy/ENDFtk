#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/gendf/SectionBase.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using namespace njoy::ENDFtk::gendf;

// trivial class to access protected constructors
class TestBase : public SectionBase {
public:
  TestBase( double ZA, double AWR, int MT,
            int NL, int NZ, int LRFLAG, int NGN,
            std::vector< DataRecord >&& lists ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN, std::move( lists ) ) {};
  template< typename Iterator >
  TestBase( const HEAD& head, Iterator& begin, const Iterator& end,
            long& lineNumber, int MAT ) :
    SectionBase( head, begin, end, lineNumber, MAT ) {};
};

// forward declarations
std::string chunk();
void verifySection( TestBase );

// tests
SCENARIO( "BaseSection tests") {

  GIVEN( "valid data for the section" ) {

    WHEN( "the data is given as a string" ) {

      std::string line = chunk();
      auto begin = line.begin();
      auto end = line.end();
      long lineNumber = 0;
      auto head = StructureDivision( begin, end, lineNumber );

      THEN( "the section can be constructed" ) {

        TestBase section( asHead(head), begin, end, lineNumber, 9228 );
        verifySection( section );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly" ) {

      std::vector< DataRecord > lists;
      std::vector<double> data1 = { 7.705020e-4, 1.023642e+3 };
      lists.emplace_back( 293.6, 2, 1, 2, std::move( data1 ) );
      std::vector<double> data2 = { 9.306457e-3, 2.031301e+2 };
      lists.emplace_back( 293.6, 2, 1, 3, std::move( data2 ) );

      THEN( "the section can be constructed" ) {

        TestBase section( 92235., 0.0, 1, 1, 1, 0, 3, std::move( lists ) );
        verifySection( section );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk(){

  return
    " 9.223500+4 0.000000+0          1          1          0          39228 3  1    1\n"
    " 2.936000+2 0.000000+0          2          1          2          29228 3  1    2\n"
    " 7.705020-4 1.023642+3                                            9228 3  1    3\n"
    " 2.936000+2 0.000000+0          2          1          2          39228 3  1    4\n"
    " 9.306457-3 2.031301+2                                            9228 3  1    5\n"
    "                                                                  9228 3  099999\n";
}

void verifySection( TestBase section ) {

  // header information
  CHECK( 1 == section.MT() );
  CHECK( 1 == section.sectionNumber() );
  CHECK( 92235 == section.ZA() );
  CHECK( 0.0 == section.atomicWeightRatio() );
  CHECK( 0.0 == section.AWR() );
  CHECK( 1 == section.NL() );
  CHECK( 1 == section.numberLegendreMoments() );
  CHECK( 0 == section.legendreOrder() );
  CHECK( 1 == section.NZ() );
  CHECK( 1 == section.numberDilutions() );
  CHECK( 0 == section.LR() );
  CHECK( 0 == section.complexBreakUp() );
  CHECK( 3 == section.NGN() );
  CHECK( 3 == section.numberGroups() );

  // access lists
  CHECK( 2 == section.records().size() );
  CHECK( 9.306457e-3 == Approx( section.record(3).list()[0] ) );
  CHECK( section.hasRecord(2) );
  CHECK( !section.hasRecord(1) );
  CHECK( !section.hasRecord(4) );

  // convenience functions
  CHECK_THROWS( section.checkBounds( 1, 1 ) );
  CHECK_THROWS( section.checkBounds( 0, 2 ) );
  CHECK_THROWS( section.checkBounds( 0, 0, 0 ) );
  CHECK_THROWS( section.checkBounds( 4, 0, 0 ) );
  CHECK_NOTHROW( section.checkBounds( 3, 0, 0 ) );
  CHECK( 7.705020e-4 == Approx( section.getValue( 0, 2, 0, 0) ) );
  CHECK( 2.031301e+2 == Approx( section.getValue( 1, 3, 0, 0) ) );
}
