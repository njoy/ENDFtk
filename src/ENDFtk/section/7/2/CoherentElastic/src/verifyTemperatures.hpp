template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  auto compare = [NP] ( const auto& entry )
                      { return entry.NPL() == NP; };

  auto iter = std::find_if_not( temperatures.begin(), temperatures.end(), compare );

  if ( iter != temperatures.end() ) {

    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={} for the temperature with index={}", NP,
               ranges::cpp20::distance( temperatures.begin(), iter ) );
    throw std::exception();
  }
}
