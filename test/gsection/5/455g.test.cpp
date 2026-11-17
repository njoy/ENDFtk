// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what is being tested
#include "ENDFtk/gsection/5/455g.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"
#include "tools/std20/algorithm.hpp"


// aliasing
using namespace njoy::ENDFtk;

std::string chunkDelayed();
std::string validSEND();

void verifyChunkDelayed( const section::GType< 5, 455 >& );

SCENARIO( "section::GType< 5, 455 >" ) {

    GIVEN( "valid data for a section::GType< 5, 455 > for delayed neutron spectra" ) {

        std::string sectionString = chunkDelayed() + validSEND();

        WHEN( "the data is provided explicitly") {

            int zaid = 92235;
            double awr = 0.0;
            int lr = 0;
            double temp = 293.6;
            int ng2 = 17;
            std::vector< double > lambda = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
            std::vector< std::vector< double > > chi = {
                { 6.40367e-13, 4.42529e-11, 1.21905e-10, 3.183440e-9, 1.757545e-7, 1.836960e-5, 5.094932e-4, 2.161763e-3,
                1.310483e-3, 5.424201e-3, 8.262024e-3, 1.267926e-2, 2.417905e-3, 2.188727e-3, 3.514090e-5, 0.0, 0.0, 0.0, 0.0, 0.0 },
                { 1.47010e-11, 1.015916e-9, 2.798589e-9, 7.308246e-8, 4.034810e-6, 4.217127e-4, 2.641997e-3, 7.052062e-3,
                3.763665e-3, 2.381035e-2, 2.873840e-2, 8.443434e-2, 1.537137e-2, 1.412648e-2, 3.337214e-4, 0.0, 0.0, 0.0, 0.0, 0.0 },
                { 9.82642e-12, 6.79059e-10, 1.870633e-9, 4.884978e-8, 2.696947e-6, 2.818813e-4, 2.111820e-3, 6.968125e-3, 3.736493e-3,
                2.457903e-2, 3.509891e-2, 8.189346e-2, 9.411334e-3, 7.045920e-3, 1.365560e-3, 1.490632e-5, 0.0, 0.0, 0.0, 0.0 },
                { 1.40367e-11, 9.70009e-10, 2.672127e-9, 6.978001e-8, 3.852484e-6, 4.026560e-4, 3.536946e-3, 1.225451e-2, 6.518136e-3,
                4.440559e-2, 6.923502e-2, 1.647387e-1, 3.265034e-2, 4.166897e-2, 1.084771e-2, 5.196002e-4, 0.0, 0.0, 0.0, 0.0 },
                { 3.84615e-12, 2.65790e-10, 7.32184e-10, 1.912027e-8, 1.055611e-6, 1.103310e-4, 1.847336e-3, 5.717616e-3, 3.382608e-3,
                2.164622e-2, 3.247626e-2, 6.442444e-2, 1.007016e-2, 1.314721e-2, 5.164237e-3, 5.877135e-4, 0.0, 0.0, 0.0, 0.0 },
                { 1.22217e-12, 8.44587e-11, 2.32662e-10, 6.075751e-9, 3.354359e-7, 3.505928e-5, 1.259095e-3, 2.981301e-3, 1.327339e-3,
                8.832828e-3, 1.292705e-2, 2.614138e-2, 4.131419e-3, 5.489045e-3, 2.801146e-3, 5.005918e-4, 0.0, 0.0, 0.0, 0.0 }
            };

            section::GType< 5, 455 > chunkDelayed( zaid, awr, lr, temp, ng2, chi, lambda );



            THEN( "a section GType< 5, 455 > can be constructed and members can be tested" ) {

                verifyChunkDelayed( chunkDelayed );

            } // THEN

            THEN( "it can be printed" ) {

                std::string buffer;
                auto output = std::back_inserter( buffer );
                chunkDelayed.print( output, 9228, 5 );

                CHECK( buffer == sectionString );
            } // THEN

        } // WHEN

        WHEN( "the data is given as a string" ) {

            std::string line = chunkDelayed() + validSEND();
            auto begin = line.begin();
            auto end = line.end();
            long lineNumber = 0;
            auto head = HeadRecord(begin, end, lineNumber);

            section::GType< 5, 455 > chunkDelayed( head, begin, end, lineNumber, 9228 );

            THEN( "a section GType< 5, 455 > can be constructed and members can be tested" ) {

                verifyChunkDelayed( chunkDelayed );

            } // THEN

            THEN( "it can be printed" ) {

                std::string buffer;
                auto output = std::back_inserter( buffer );
                chunkDelayed.print( output, 9228, 5 );

                CHECK( buffer == sectionString );
            } // THEN
        } // WHEN
    } // GIVEN
} // SCENARIO



std::string chunkDelayed() {
    return
   " 9.223500+4 0.000000+0          6          1          0         209228 5455     \n"
   " 2.936000+2 0.000000+0         17          1        102         209228 5455     \n"
   " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+09228 5455     \n"
   " 6.40367-13 1.47010-11 9.82642-12 1.40367-11 3.84615-12 1.22217-129228 5455     \n"
   " 4.42529-11 1.015916-9 6.79059-10 9.70009-10 2.65790-10 8.44587-119228 5455     \n"
   " 1.21905-10 2.798589-9 1.870633-9 2.672127-9 7.32184-10 2.32662-109228 5455     \n"
   " 3.183440-9 7.308246-8 4.884978-8 6.978001-8 1.912027-8 6.075751-99228 5455     \n"
   " 1.757545-7 4.034810-6 2.696947-6 3.852484-6 1.055611-6 3.354359-79228 5455     \n"
   " 1.836960-5 4.217127-4 2.818813-4 4.026560-4 1.103310-4 3.505928-59228 5455     \n"
   " 5.094932-4 2.641997-3 2.111820-3 3.536946-3 1.847336-3 1.259095-39228 5455     \n"
   " 2.161763-3 7.052062-3 6.968125-3 1.225451-2 5.717616-3 2.981301-39228 5455     \n"
   " 1.310483-3 3.763665-3 3.736493-3 6.518136-3 3.382608-3 1.327339-39228 5455     \n"
   " 5.424201-3 2.381035-2 2.457903-2 4.440559-2 2.164622-2 8.832828-39228 5455     \n"
   " 8.262024-3 2.873840-2 3.509891-2 6.923502-2 3.247626-2 1.292705-29228 5455     \n"
   " 1.267926-2 8.443434-2 8.189346-2 1.647387-1 6.442444-2 2.614138-29228 5455     \n"
   " 2.417905-3 1.537137-2 9.411334-3 3.265034-2 1.007016-2 4.131419-39228 5455     \n"
   " 2.188727-3 1.412648-2 7.045920-3 4.166897-2 1.314721-2 5.489045-39228 5455     \n"
   " 3.514090-5 3.337214-4 1.365560-3 1.084771-2 5.164237-3 2.801146-39228 5455     \n"
   " 0.000000+0 0.000000+0 1.490632-5 5.196002-4 5.877135-4 5.005918-49228 5455     \n";

}

std::string validSEND() {
    return
    "                                                                  9228 5  0     \n";
}

void verifyChunkDelayed( const section::GType< 5, 455 >& chunk ) {
    CHECK( 92235 == chunk.ZA() );
    CHECK( 92235 == chunk.targetIdentifier() );
    CHECK( 455 == chunk.MT() );
    CHECK( 455 == chunk.sectionNumber() );
    CHECK( 20 == chunk.NGN() );
    CHECK( 20 == chunk.numberNeutronGroups() );
    CHECK( 1 == chunk.NZ() );
    CHECK( 1 == chunk.numberDilutions() );
    CHECK( 6 == chunk.NT() );
    CHECK( 6 == chunk.numberTimeConstants() );
    CHECK( 0 == chunk.LR() );
    CHECK( 0 == chunk.breakUp() );
    CHECK_THAT( 293.6, WithinRel( chunk.TEMP() ) );
    CHECK_THAT( 293.6, WithinRel( chunk.temperature() ) );
    std::vector< double > expected_lambda = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    std::vector< std::vector< double > > expected_chi = {
        { 6.40367e-13, 4.42529e-11, 1.21905e-10, 3.183440e-9, 1.757545e-7, 1.836960e-5, 5.094932e-4, 2.161763e-3,
          1.310483e-3, 5.424201e-3, 8.262024e-3, 1.267926e-2, 2.417905e-3, 2.188727e-3, 3.514090e-5, 0.0, 0.0, 0.0, 0.0, 0.0 },
        { 1.47010e-11, 1.015916e-9, 2.798589e-9, 7.308246e-8, 4.034810e-6, 4.217127e-4, 2.641997e-3, 7.052062e-3,
          3.763665e-3, 2.381035e-2, 2.873840e-2, 8.443434e-2, 1.537137e-2, 1.412648e-2, 3.337214e-4, 0.0, 0.0, 0.0, 0.0, 0.0 },
        { 9.82642e-12, 6.79059e-10, 1.870633e-9, 4.884978e-8, 2.696947e-6, 2.818813e-4, 2.111820e-3, 6.968125e-3, 3.736493e-3,
          2.457903e-2, 3.509891e-2, 8.189346e-2, 9.411334e-3, 7.045920e-3, 1.365560e-3, 1.490632e-5, 0.0, 0.0, 0.0, 0.0 },
        { 1.40367e-11, 9.70009e-10, 2.672127e-9, 6.978001e-8, 3.852484e-6, 4.026560e-4, 3.536946e-3, 1.225451e-2, 6.518136e-3,
          4.440559e-2, 6.923502e-2, 1.647387e-1, 3.265034e-2, 4.166897e-2, 1.084771e-2, 5.196002e-4, 0.0, 0.0, 0.0, 0.0 },
        { 3.84615e-12, 2.65790e-10, 7.32184e-10, 1.912027e-8, 1.055611e-6, 1.103310e-4, 1.847336e-3, 5.717616e-3, 3.382608e-3,
          2.164622e-2, 3.247626e-2, 6.442444e-2, 1.007016e-2, 1.314721e-2, 5.164237e-3, 5.877135e-4, 0.0, 0.0, 0.0, 0.0 },
        { 1.22217e-12, 8.44587e-11, 2.32662e-10, 6.075751e-9, 3.354359e-7, 3.505928e-5, 1.259095e-3, 2.981301e-3, 1.327339e-3,
          8.832828e-3, 1.292705e-2, 2.614138e-2, 4.131419e-3, 5.489045e-3, 2.801146e-3, 5.005918e-4, 0.0, 0.0, 0.0, 0.0 }
    };
    for ( size_t t = 0; t < static_cast< std::size_t >( chunk.NT() ); ++t ) {
        CHECK_THAT( expected_lambda[t], WithinRel( chunk.lambda()[t] ) );
        for ( size_t g = 0; g < static_cast< std::size_t >( chunk.NGN() ); ++g ) {
            CHECK_THAT( expected_chi[t][g], WithinRel( chunk.chi(t)[g] ) );
        }
    }

}
