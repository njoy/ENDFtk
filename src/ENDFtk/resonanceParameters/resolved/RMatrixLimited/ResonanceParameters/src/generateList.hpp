static ListRecord
generateList( std::vector< double >&& energies,
              std::vector< std::vector< double > >&& parameters ) {

  unsigned int nrs = energies.size();
  if ( parameters.size() != nrs ) {

    Log::info( "The number of resonance energies and resonance parameters is "
               "not consistent" );
    Log::info( "NRS value: {}", nrs );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "parameters.size(): {}", parameters.size() );
    throw std::exception();
  }

  unsigned int nch = parameters.front().size();
  unsigned int padding = ( 6 - ( ( 1 + nch ) % 6 ) ) % 6;
  unsigned int nx = nrs * ( 1 + nch + padding ) / 6;

  std::vector< double > list;
  for ( unsigned int i = 0; i < nrs; ++i ) {

    list.push_back( energies[i] );
    list.insert( list.end(), parameters[i].begin(), parameters[i].end() );
    list.insert( list.end(), padding, 0.0 );
  }
  return ListRecord( 0.0, 0.0, 0, nrs, nx, std::move( list ) );
}
