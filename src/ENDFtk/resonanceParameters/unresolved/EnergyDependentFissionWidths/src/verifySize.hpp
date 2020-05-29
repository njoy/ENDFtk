template < typename Range >
static void
verifySize( unsigned int NE, const Range& lvalues ) {

  for ( unsigned int i = 0; i < lvalues.size(); ++i ) {

    if ( NE != lvalues[i].NE() ) {

      Log::error( "All fission width functions must have the same size" );
      Log::info( "Expected NE={} for the l value with index={}", NE, i );
      throw std::exception();
    }
  }
}
