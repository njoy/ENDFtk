template< typename Array >
static void
verifyBetaValues( double beta, const Array& range ) {

  auto compare = [beta] ( const auto& entry )
                        { return entry != beta; };

  auto iter = std::find_if( range.begin(), range.end(), compare );
  bool inconsistent = ( range.end() != iter );
  if ( inconsistent ) {

    Log::error( "Encountered inconsistent beta values within a BetaValue" );
    Log::info( "Expected: {}", beta );
    Log::info( "Found: {}", *iter );
    throw std::exception();
  }
}
