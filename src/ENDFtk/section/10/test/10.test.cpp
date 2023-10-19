// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/10.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct = section::Type< 10 >::ReactionProduct;

std::string chunk();
void verifyChunk( const section::Type< 10 >& );
std::string validSEND();
std::string invalidSEND();

SCENARIO( "section::Type< 10 >" ) {

  GIVEN( "valid data for a section::Type< 10 >" ) {

    std::string sectionString = chunk() + validSEND();

    WHEN( "the data is given explicitly" ) {

      int mt = 102;
      int zaid = 95241;
      int lis = 0;
      double awr = 2.389860e+2;

      std::vector< ReactionProduct > products = {

        ReactionProduct( 5.537755e+6, 5.537755e+6, 95242, 0,
                         { 2 }, { 3 }, { 1e-5, 3e+7 }, { 0.9, 0.52 } ),
        ReactionProduct( 5.537755e+6, 5.489125e+6, 95242, 2,
                         { 2 }, { 3 }, { 1e-5, 3e+7 }, { 0.1, 0.48 } ) };

      section::Type< 10 > chunk( mt, zaid, awr, lis,
                                 std::move( products ) );

      THEN( "a section::Type< 10 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 10 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 0;
      HeadRecord head( begin, end, lineNumber );

      section::Type< 10 > chunk( head, begin, end, lineNumber, 9543 );

      THEN( "a section::Type< 10 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 10 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN

    WHEN( "there is a tree::Section" ) {

      tree::Section section( 9543, 10, 102, std::string( sectionString ) );

      section::Type< 10 > chunk = section.parse< 10 >();

      THEN( "a section::Type< 10 > can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9543, 10 );

        CHECK( buffer == sectionString );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a section::Type< 10 >" ) {

    WHEN( "a string representation of a section::Type< 10 > with "
          "an invalid SEND" ) {

      std::string sectionString = chunk() + invalidSEND();
      auto begin = sectionString.begin();
      auto end = sectionString.end();
      long lineNumber = 1;
      HeadRecord head( begin, end, lineNumber );

      THEN( "an exception is thrown" ){

        CHECK_THROWS( section::Type< 10 >( head, begin, end,
                                           lineNumber, 9543 ) );
      } // THEN
    } // WHEN
  } // THEN
} // SCENARIO

std::string chunk() {

  return
    " 9.524100+4 2.389860+2          0          0          2          0954310102     \n"
    " 5.537755+6 5.537755+6      95242          0          1          2954310102     \n"
    "          2          3                                            954310102     \n"
    " 1.000000-5 9.000000-1 3.000000+7 5.200000-1                      954310102     \n"
    " 5.537755+6 5.489125+6      95242          2          1          2954310102     \n"
    "          2          3                                            954310102     \n"
    " 1.000000-5 1.000000-1 3.000000+7 4.800000-1                      954310102     \n";
}

void verifyChunk( const section::Type< 10 >& chunk ) {

  CHECK( 102 == chunk.MT() );
  CHECK( 95241 == chunk.ZA() );
  CHECK_THAT( 2.389860e+2, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 2.389860e+2, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK( 0 == chunk.LIS() );
  CHECK( 0 == chunk.excitedLevel() );
  CHECK( 2 == chunk.NS() );
  CHECK( 2 == chunk.numberReactionProducts() );

  CHECK( 2 == chunk.reactionProducts().size() );

  auto product = chunk.reactionProducts()[0];
  CHECK_THAT( 5.537755e+6, WithinRel( product.QM() ) );
  CHECK_THAT( 5.537755e+6, WithinRel( product.massDifferenceQValue() ) );
  CHECK_THAT( 5.537755e+6, WithinRel( product.QI() ) );
  CHECK_THAT( 5.537755e+6, WithinRel( product.reactionQValue() ) );
  CHECK( 95242 == product.IZAP() );
  CHECK( 95242 == product.productIdentifier() );
  CHECK( 0 == product.LFS() );
  CHECK( 0 == product.excitedLevel() );
  CHECK( 2 == product.NP() );
  CHECK( 1 == product.NR() );
  CHECK( 1 == product.interpolants().size() );
  CHECK( 1 == product.boundaries().size() );
  CHECK( 3 == product.interpolants()[0] );
  CHECK( 2 == product.boundaries()[0] );
  CHECK( 2 == product.E().size() );
  CHECK( 2 == product.energies().size() );
  CHECK( 2 == product.XS().size() );
  CHECK( 2 == product.crossSections().size() );
  CHECK_THAT( 1e-5, WithinRel( product.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( product.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( product.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( product.energies()[1] ) );
  CHECK_THAT( 0.9, WithinRel( product.XS()[0] ) );
  CHECK_THAT( 0.52, WithinRel( product.XS()[1] ) );
  CHECK_THAT( 0.9, WithinRel( product.crossSections()[0] ) );
  CHECK_THAT( 0.52, WithinRel( product.crossSections()[1] ) );

  product = chunk.reactionProducts()[1];
  CHECK_THAT( 5.537755e+6, WithinRel( product.QM() ) );
  CHECK_THAT( 5.537755e+6, WithinRel( product.massDifferenceQValue() ) );
  CHECK_THAT( 5.489125e+6, WithinRel( product.QI() ) );
  CHECK_THAT( 5.489125e+6, WithinRel( product.reactionQValue() ) );
  CHECK( 95242 == product.IZAP() );
  CHECK( 95242 == product.productIdentifier() );
  CHECK( 2 == product.LFS() );
  CHECK( 2 == product.excitedLevel() );
  CHECK( 2 == product.NP() );
  CHECK( 1 == product.NR() );
  CHECK( 1 == product.interpolants().size() );
  CHECK( 1 == product.boundaries().size() );
  CHECK( 3 == product.interpolants()[0] );
  CHECK( 2 == product.boundaries()[0] );
  CHECK( 2 == product.E().size() );
  CHECK( 2 == product.energies().size() );
  CHECK( 2 == product.XS().size() );
  CHECK( 2 == product.crossSections().size() );
  CHECK_THAT( 1e-5, WithinRel( product.E()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( product.E()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( product.energies()[0] ) );
  CHECK_THAT( 3e+7, WithinRel( product.energies()[1] ) );
  CHECK_THAT( 0.1, WithinRel( product.XS()[0] ) );
  CHECK_THAT( 0.48, WithinRel( product.XS()[1] ) );
  CHECK_THAT( 0.1, WithinRel( product.crossSections()[0] ) );
  CHECK_THAT( 0.48, WithinRel( product.crossSections()[1] ) );

  CHECK( 7 == chunk.NC() );
}

std::string validSEND(){
  return
    "                                                                  954310  0     \n";
}

std::string invalidSEND(){
  return
    "                                                                  954310  1     \n";
}
