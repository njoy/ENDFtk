template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  auto compare = [NP] ( const auto& entry )
                      { return entry.NPL() == NP; };

  auto iter = std::find_if_not( temperatures.begin(), temperatures.end(), compare );

  if ( iter != temperatures.end() ) {

    using namespace njoy::tools;
    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={} for the temperature with index={}", NP,
               std20::ranges::distance( temperatures.begin(), iter ) );
    throw std::exception();
  }
}
