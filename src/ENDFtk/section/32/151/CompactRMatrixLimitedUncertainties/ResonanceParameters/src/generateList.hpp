static ListRecord
generateList( std::vector< double >&& energies,
              std::vector< std::vector< double > >&& parameters,
              std::vector< double >&& denergies,
              std::vector< std::vector< double > >&& dparameters ) {

  unsigned int nrs = energies.size();
  if ( ( parameters.size() != nrs ) || ( denergies.size() != nrs ) ||
       ( dparameters.size() != nrs ) ) {

    Log::info( "The number of resonance energies and resonance parameters is "
               "not consistent" );
    Log::info( "NRS value: {}", nrs );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "parameters.size(): {}", parameters.size() );
    Log::info( "denergies.size(): {}", denergies.size() );
    Log::info( "dparameters.size(): {}", dparameters.size() );
    throw std::exception();
  }

  if ( nrs == 0 ) {

    Log::info( "No resonances are given" );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "parameters.size(): {}", parameters.size() );
    Log::info( "denergies.size(): {}", denergies.size() );
    Log::info( "dparameters.size(): {}", dparameters.size() );
    throw std::exception();
  }

  unsigned int nch = parameters.front().size();
  unsigned int padding = ( 6 - ( ( 1 + nch ) % 6 ) ) % 6;
  unsigned int nx = nrs * ( 1 + nch + padding ) / 6;

  std::vector< double > list;
  for ( unsigned int i = 0; i < nrs; ++i ) {

    if ( ( parameters[i].size() != nch ) || ( parameters[i].size() != nch ) ) {

      Log::info( "The number of channels for the resonance energy with index {}"
                 "is not equal to the expected value", i );
      Log::info( "NCH value: {}", nch );
      Log::info( "parameters[i].size(): {}", parameters[i].size() );
      Log::info( "dparameters[i].size(): {}", dparameters[i].size() );
      throw std::exception();
    }

    list.push_back( energies[i] );
    list.insert( list.end(), parameters[i].begin(), parameters[i].end() );
    list.insert( list.end(), padding, 0.0 );
    list.push_back( denergies[i] );
    list.insert( list.end(), dparameters[i].begin(), dparameters[i].end() );
    list.insert( list.end(), padding, 0.0 );
  }
  return ListRecord( 0.0, 0.0, 0, nrs, nx, std::move( list ) );
}
