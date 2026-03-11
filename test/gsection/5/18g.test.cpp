// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what is being tested
#include "ENDFtk/gsection/5/18g.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"
#include "tools/std20/algorithm.hpp"


// aliasing
using namespace njoy::ENDFtk;

std::string chunkPrompt();
std::string validSEND();

void verifyChunkPrompt( const section::GType< 5, 18 >& );

SCENARIO( "section::GType< 5, 18 >" ) {

    GIVEN( "valid data for a section::GType< 5, 18 > for prompt fission neutron spectra" ) {

        std::string sectionString = chunkPrompt() + validSEND();

        WHEN( "the data is provided explicitly" ){

            int zaid = 92235;
            double awr = 0.0;
            int lr = 0;
            double temp = 293.6;
            std::vector< double > chi = { 1.96730e-14, 1.15287e-11, 7.10093e-11, 7.358034e-9, 9.678216e-7, 9.976067e-5,
                  8.080721e-4, 4.412081e-3, 3.119482e-3, 2.172044e-2, 4.250824e-2, 1.727228e-1,
                  6.932789e-2, 1.778175e-1, 2.204227e-1, 2.772107e-1, 8.677879e-3, 1.124378e-3,
                  1.884936e-5, 8.232639e-6 };

            section::GType< 5, 18 > chunkPrompt( zaid, awr, lr, temp, chi );

            THEN( " a section GType< 5, 18 > can be constructed and members can be tested" ) {

                verifyChunkPrompt( chunkPrompt );

            } // THEN

            THEN( "it can be printed ") {

                std::string buffer;
                auto output = std::back_inserter( buffer );
                chunkPrompt.print( output, 9228, 5 );

                CHECK( buffer == sectionString );
            } // THEN
        } // WHEN

        WHEN( "the data is given as a string" ) {

            std::string line = chunkPrompt() + validSEND();
            auto begin = line.begin();
            auto end = line.end();
            long lineNumber = 0;
            auto head = HeadRecord( begin, end, lineNumber );

            section::GType< 5, 18 > chunkPrompt( head, begin, end, lineNumber, 9228 );

            THEN( "a section GType< 5, 18 > can be constructed and members can be tested" ) {

                verifyChunkPrompt( chunkPrompt );

            } // THEN

            THEN( "it can be printed ") {

                std::string buffer;
                auto output = std::back_inserter( buffer );
                chunkPrompt.print( output, 9228, 5 );

                CHECK( buffer == sectionString );
            } // THEN
        } // WHEN
    } // GIVEN
} // SCENARIO

std::string chunkPrompt() {
    return
   " 9.223500+4 0.000000+0          1          1          0         209228 5 18     \n"
   " 2.936000+2 0.000000+0         20          1         20         209228 5 18     \n"
   " 1.96730-14 1.15287-11 7.10093-11 7.358034-9 9.678216-7 9.976067-59228 5 18     \n"
   " 8.080721-4 4.412081-3 3.119482-3 2.172044-2 4.250824-2 1.727228-19228 5 18     \n"
   " 6.932789-2 1.778175-1 2.204227-1 2.772107-1 8.677879-3 1.124378-39228 5 18     \n"
   " 1.884936-5 8.232639-6                                            9228 5 18     \n";
}

std::string validSEND() {
    return
    "                                                                  9228 5  0     \n";
}


void verifyChunkPrompt( const section::GType< 5, 18 >& chunk ) {
    CHECK( 92235 == chunk.ZA() );
    CHECK( 92235 == chunk.targetIdentifier() );
    CHECK( 18 == chunk.MT() );
    CHECK( 18 == chunk.sectionNumber() );
    CHECK( 20 == chunk.NGN() );
    CHECK( 20 == chunk.numberNeutronGroups() );
    CHECK( 1 == chunk.NZ() );
    CHECK( 1 == chunk.numberDilutions() );
    CHECK( 0 == chunk.LR() );
    CHECK( 0 == chunk.breakUp() );
    CHECK_THAT( 293.6, WithinRel( chunk.TEMP() ) );
    CHECK_THAT( 293.6, WithinRel( chunk.temperature() ) );
    std::vector< double > expected_chi = { 1.96730e-14, 1.15287e-11, 7.10093e-11, 7.358034e-9, 9.678216e-7, 9.976067e-5,
                                           8.080721e-4, 4.412081e-3, 3.119482e-3, 2.172044e-2, 4.250824e-2, 1.727228e-1,
                                           6.932789e-2, 1.778175e-1, 2.204227e-1, 2.772107e-1, 8.677879e-3, 1.124378e-3,
                                           1.884936e-5, 8.232639e-6 };
    for ( size_t g = 0; g < static_cast< std::size_t >( chunk.NGN() ); ++g ) {
        CHECK_THAT( expected_chi[g], WithinRel( chunk.chi()[g] ) );
    }

}