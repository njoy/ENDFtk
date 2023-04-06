static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& spins,
              std::vector< double >&& column1,
              std::vector< double >&& column2,
              std::vector< double >&& column3,
              std::vector< double >&& column4,
              std::vector< double >&& values ) {

  unsigned int nrb = energies.size();
  if ( ( spins.size() != nrb ) or ( column1.size() != nrb ) or
       ( column2.size() != nrb ) or ( column3.size() != nrb ) or
       ( column4.size() != nrb ) ) {

    Log::info( "The number of resonances and the resonance parameters are not "
               "consistent" );
    Log::info( "NRS value: {}", nrb );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "spins.size(): {}", spins.size() );
    Log::info( "column1.size(): {}", column1.size() );
    Log::info( "column2.size(): {}", column2.size() );
    Log::info( "column3.size(): {}", column3.size() );
    Log::info( "column4.size(): {}", column4.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nrb; ++i ) {

    list.push_back( energies[i] );
    list.push_back( spins[i] );
    list.push_back( column1[i] );
    list.push_back( column2[i] );
    list.push_back( column3[i] );
    list.push_back( column4[i] );
  }
  list.insert( list.end(), values.begin(), values.end() );
  return list;
}
