template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  auto iter = std::find_if_not( temperatures.begin(), temperatures.end(),
                                [NP] ( const auto& temperature )
                                     { return NP == temperature.NPL(); } );

  if ( iter != temperatures.end() ) {

    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={} for the temperature with index={}", NP,
               std::distance( temperatures.begin(), iter ) );
    throw std::exception();
  }
}
