template < typename Range >
static void
verifySize( const Range& jvalues ) {

  if ( jvalues.size() == 0 ) {

    Log::error( "At least one J value must be given" );
    throw std::exception();
  }

  unsigned int NE = jvalues.front().NE();
  for ( unsigned int i = 0; i < jvalues.size(); ++i ) {

    if ( NE != jvalues[i].NE() ) {

      Log::error( "All fission width functions must have the same size" );
      Log::info( "Expected NE={} for the J value with index={}, found NE={}",
                 NE, i, jvalues[i].NE() );
      throw std::exception();
    }
  }
}
