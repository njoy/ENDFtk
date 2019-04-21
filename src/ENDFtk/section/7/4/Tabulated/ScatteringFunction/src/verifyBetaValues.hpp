template< typename Array >
static void
verifyBetaValues( double beta, const Array& range ) {

  auto iter = std::find_if( range.begin(), range.end(),
                            [ beta ] ( const auto& v ) { return v != beta; } );
  bool inconsistent = ( range.end() != iter );
  if ( inconsistent ) {

    Log::error( "Encountered inconsistent beta values within a BetaValue" );
    Log::info( "Expected: {}", beta );
    Log::info( "Found: {}", *iter );
    throw std::exception();
  }
}
