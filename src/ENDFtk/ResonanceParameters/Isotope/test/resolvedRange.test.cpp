#include <typeinfo>
#include <type_traits>

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

auto isSLBW = [](const auto& s ){ 
  return std::is_same<std::decay_t<decltype(s)>, 
                      ResonanceParameters::Resolved::SLBW >::value; };
auto isMLBW = [](const auto& s ){ 
  return std::is_same<std::decay_t<decltype(s)>, 
                      ResonanceParameters::Resolved::MLBW >::value; };
auto isReichMoore = [](const auto& s ){ 
  return std::is_same<std::decay_t<decltype(s)>, 
                      ResonanceParameters::Resolved::ReichMoore >::value; };

SCENARIO( "Determining what resolved resonance Range" ){
  GIVEN( "string representation" ){
  std::string resonanceRepresentation{
    // " 6.114800+4 1.466500+2          0          0          1          06153 2151    1\n"
    // " 6.114800+4 1.000000+0          0          0          1          06153 2151    2\n"
    // " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
    " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
    " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
    " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n"};
  auto begin = resonanceRepresentation.begin();
  auto end = resonanceRepresentation.end();
  long lineNumber = 0;
  int MAT = 6153;
  int MF = 2;
  int MT = 151;

    WHEN( "trying to create a SLBW range" ){
      njoy::Log::info( "Looking for SLBW" );
      CONT cont( 1E-4, 1.0, 1, 1, 0, 0 );
      auto range = ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT );
      REQUIRE( std::visit( isSLBW, range ) );
      REQUIRE( not std::visit( isMLBW, range ) );
      REQUIRE( not std::visit( isReichMoore, range ) );

    }
    WHEN( "trying to create a MLBW range" ){
      njoy::Log::info( "Looking for MLBW" );
      CONT cont( 1E-4, 1.0, 1, 2, 0, 0 );
      auto range = ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT );
      REQUIRE( std::visit( isMLBW, range ) );
      REQUIRE( not std::visit( isSLBW, range ) );
      REQUIRE( not std::visit( isReichMoore, range ) );
    }
    WHEN( "trying to create a ReichMoore range" ){
      njoy::Log::info( "Looking for ReichMoore" );
      CONT cont( 1E-4, 1.0, 1, 3, 0, 0 );
      auto range = ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT );
      REQUIRE( std::visit( isReichMoore, range ) );
      REQUIRE( not std::visit( isSLBW, range ) );
      REQUIRE( not std::visit( isMLBW, range ) );
    }
    WHEN( "trying to create a Adler-Adler range" ){
      njoy::Log::info( "Looking for Adler-Adler" );
      CONT cont( 1E-4, 1.0, 1, 4, 0, 0 );
      REQUIRE_THROWS( ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT ) );
    }
    WHEN( "trying to create a R-Matrix Limited range" ){
      njoy::Log::info( "Looking for R-Matrix Limited" );
      CONT cont( 1E-4, 1.0, 1, 7, 0, 0 );
      REQUIRE_THROWS( ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT ) );
    }
    WHEN( "trying to create an invalid range" ){
      njoy::Log::info( "Looking for invalid" );
      CONT cont( 1E-4, 1.0, 1, 5, 0, 0 );
      REQUIRE_THROWS( ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT ) );
    }
    WHEN( "trying to create an invalid range" ){
      njoy::Log::info( "Looking for invalid" );
      CONT cont( 1E-4, 1.0, 1, 6, 0, 0 );
      REQUIRE_THROWS( ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT ) );
    }
    WHEN( "trying to create an invalid range" ){
      njoy::Log::info( "Looking for invalid" );
      CONT cont( 1E-4, 1.0, 1, 16, 0, 0 );
      REQUIRE_THROWS( ResonanceParameters::Isotope::resolvedRange( cont, begin, end, 
                                                                lineNumber,
                                                                MAT, MF, MT ) );
    }
  }
}