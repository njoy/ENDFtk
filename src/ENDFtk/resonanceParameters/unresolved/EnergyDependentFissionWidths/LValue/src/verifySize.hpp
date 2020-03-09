template < typename Range >
static void
verifySize( unsigned int NE, const Range& jvalues ) {

  if ( jvalues.size() == 0 ) {

    Log::error( "At least one J value must be given" );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < jvalues.size(); ++i ) {

    if ( NE != jvalues[i].NE() ) {

      Log::error( "All fission width functions must have the same size" );
      Log::info( "Expected NE={} for the J value with index={}", NE, i );
      throw std::exception();
    }
  }
}
