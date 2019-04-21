template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  // lambdas for verifying
  auto verifySize = [NP] ( const auto& value ) -> bool
                         { return value.NPL() == NP; };
  auto sum = [] ( bool left, bool right ) -> bool
                { return left and right; };

  if ( ranges::accumulate(
         temperatures | ranges::view::transform( verifySize ),
         true,
         sum ) == false ) {

    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={}", NP );
    throw std::exception();
  }
}
