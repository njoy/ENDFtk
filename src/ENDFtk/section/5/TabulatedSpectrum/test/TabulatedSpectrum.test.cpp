#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

// convenience typedefs
using TabulatedSpectrum = 
section::Type< 5 >::TabulatedSpectrum;
using OutgoingDistribution = 
section::Type< 5 >::TabulatedSpectrum::OutgoingDistribution;

std::string chunk();

SCENARIO( "Tabulated" ) {

  GIVEN( "valid data for a Tabulated thermal scattering law with one "
         "temperature" ) {

    std::vector< long > boundaries = { 2 };
    std::vector< long > interpolants = { 4 };
    std::vector< OutgoingDistribution > outgoing = {
        OutgoingDistribution( 1e-5, { 3 }, { 2 },
                              { 0.0, 1e+5, 3e+7 },
                              { 0.0, 1.757570e-9, 1.843350e-9 } ),
        OutgoingDistribution( 3e+7, { 4 }, { 2 },
                              { 0.0, 10., 11., 3e+7 },
                              { 0.0, 1.733405e-9, 1.818010e-9, 1.898849e-9 } ) };

    THEN( "a TabulatedSpectrum can be constructed" ) {
      TabulatedSpectrum chunk( std::move( boundaries ), std::move( interpolants ),
                               std::move( outgoing ) );

      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 4 == chunk.interpolants()[0] );

      auto value = chunk.outgoingDistributions()[0];
      REQUIRE( 1e-5 == Approx( value.incidentEnergy() ) );
      REQUIRE( 3 == value.NP() );
      REQUIRE( 1 == value.NR() );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 2 == value.interpolants()[0] );
      REQUIRE( 3 == value.boundaries()[0] );
      REQUIRE( 3 == value.energies().size() );
      REQUIRE( 3 == value.values().size() );
      REQUIRE( 0.0 == Approx( value.energies()[0] ) );
      REQUIRE( 1e+5 == Approx( value.energies()[1] ) );
      REQUIRE( 3e+7 == Approx( value.energies()[2] ) );
      REQUIRE( 0. == Approx( value.values()[0] ) );
      REQUIRE( 1.757570e-9 == Approx( value.values()[1] ) );
      REQUIRE( 1.843350e-9 == Approx( value.values()[2] ) );

      value = chunk.outgoingDistributions()[1];
      REQUIRE( 3e+7 == Approx( value.incidentEnergy() ) );
      REQUIRE( 4 == value.NP() );
      REQUIRE( 1 == value.NR() );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 2 == value.interpolants()[0] );
      REQUIRE( 4 == value.boundaries()[0] );
      REQUIRE( 4 == value.energies().size() );
      REQUIRE( 4 == value.values().size() );
      REQUIRE( 0.0 == Approx( value.energies()[0] ) );
      REQUIRE( 10. == Approx( value.energies()[1] ) );
      REQUIRE( 11. == Approx( value.energies()[2] ) );
      REQUIRE( 3e+7 == Approx( value.energies()[3] ) );
      REQUIRE( 0. == Approx( value.values()[0] ) );
      REQUIRE( 1.733405e-9 == Approx( value.values()[1] ) );
      REQUIRE( 1.818010e-9 == Approx( value.values()[2] ) );
      REQUIRE( 1.898849e-9 == Approx( value.values()[3] ) );

      REQUIRE( 9 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a string representation of a valid TabulatedSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;

    THEN( "a TabulatedSpectrum can "
          "be constructed and members can be tested" ) {
      TabulatedSpectrum chunk( begin, end, lineNumber, 9437, 5, 18 );

      REQUIRE( 1 == chunk.NR() );
      REQUIRE( 2 == chunk.NE() );
      REQUIRE( 1 == chunk.boundaries().size() );
      REQUIRE( 2 == chunk.boundaries()[0] );
      REQUIRE( 1 == chunk.interpolants().size() );
      REQUIRE( 4 == chunk.interpolants()[0] );

      auto value = chunk.outgoingDistributions()[0];
      REQUIRE( 1e-5 == Approx( value.incidentEnergy() ) );
      REQUIRE( 3 == value.NP() );
      REQUIRE( 1 == value.NR() );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 2 == value.interpolants()[0] );
      REQUIRE( 3 == value.boundaries()[0] );
      REQUIRE( 3 == value.energies().size() );
      REQUIRE( 3 == value.values().size() );
      REQUIRE( 0.0 == Approx( value.energies()[0] ) );
      REQUIRE( 1e+5 == Approx( value.energies()[1] ) );
      REQUIRE( 3e+7 == Approx( value.energies()[2] ) );
      REQUIRE( 0. == Approx( value.values()[0] ) );
      REQUIRE( 1.757570e-9 == Approx( value.values()[1] ) );
      REQUIRE( 1.843350e-9 == Approx( value.values()[2] ) );

      value = chunk.outgoingDistributions()[1];
      REQUIRE( 3e+7 == Approx( value.incidentEnergy() ) );
      REQUIRE( 4 == value.NP() );
      REQUIRE( 1 == value.NR() );
      REQUIRE( 1 == value.interpolants().size() );
      REQUIRE( 1 == value.boundaries().size() );
      REQUIRE( 2 == value.interpolants()[0] );
      REQUIRE( 4 == value.boundaries()[0] );
      REQUIRE( 4 == value.energies().size() );
      REQUIRE( 4 == value.values().size() );
      REQUIRE( 0.0 == Approx( value.energies()[0] ) );
      REQUIRE( 10. == Approx( value.energies()[1] ) );
      REQUIRE( 11. == Approx( value.energies()[2] ) );
      REQUIRE( 3e+7 == Approx( value.energies()[3] ) );
      REQUIRE( 0. == Approx( value.values()[0] ) );
      REQUIRE( 1.733405e-9 == Approx( value.values()[1] ) );
      REQUIRE( 1.818010e-9 == Approx( value.values()[2] ) );
      REQUIRE( 1.898849e-9 == Approx( value.values()[3] ) );

      REQUIRE( 9 == chunk.NC() );
    }
  } // GIVEN

  GIVEN( "a valid instance of TabulatedSpectrum" ) {

    std::string string = chunk();
    auto begin = string.begin();
    auto end = string.end();
    long lineNumber = 1;
    TabulatedSpectrum chunk(begin, end, lineNumber, 9437, 5, 18 );

    THEN( "it can be printed" ) {
      std::string buffer;
      auto output = std::back_inserter( buffer );
      chunk.print( output, 9437, 5, 18 );
      REQUIRE( buffer == string );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n"
    "          2          4                                            9437 5 18     \n"
    " 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n"
    "          3          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n"
    " 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n"
    "          4          2                                            9437 5 18     \n"
    " 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n"
    " 3.000000+7 1.898849-9                                            9437 5 18     \n";
}

