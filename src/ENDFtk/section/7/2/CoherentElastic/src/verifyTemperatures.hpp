template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  // lambdas for verifying
  auto verifySize = [NP] ( const auto& value ) -> bool
                         { return value.NPL() == NP; };

  auto verify = temperatures | ranges::view::transform( verifySize );

  auto iter = ranges::find_if_not( verify, hana::equal.to( true ) );

  if ( iter != ranges::end( verify ) ) {

    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={} for the temperature with index={}", NP,
               std::distance( ranges::begin( verify ), iter ) );
    throw std::exception();
  }
}
