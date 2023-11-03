static std::vector< double >
generateList( std::vector< double >&& ek,
              std::vector< double >&& fk ) {

  if ( ek.size() != fk.size() ) {

    Log::error( "The number of energies and F values are not consistent" );
    Log::info( "energies.size(): {}", ek.size() );
    Log::info( "fvalues.size(): {}", fk.size() );
    throw std::exception();
  }

  std::vector< double > list;

  for ( unsigned int i = 0; i < ek.size(); ++i ) {

    list.push_back( ek[i] );
    list.push_back( fk[i] );
  }

  return list;
}

static std::vector< double >
generateList( std::vector< double >&& ek,
              std::vector< double >&& fk,
              std::vector< double >&& el,
              std::vector< double >&& fl ) {

  if ( ek.size() != fk.size() ) {

    Log::error( "The number of first array energies and F values "
                "are not consistent" );
    Log::info( "energies.size(): {}", ek.size() );
    Log::info( "fvalues.size(): {}", fk.size() );
    throw std::exception();
  }

  else if ( el.size() != fl.size() ) {

    Log::error( "The number of second array energies and F values "
                "are not consistent" );
    Log::info( "energies.size(): {}", el.size() );
    Log::info( "fvalues.size(): {}", fl.size() );
    throw std::exception();
  }

  std::vector< double > list;

  for ( unsigned int i = 0; i < ek.size(); ++i ) {

    list.push_back( ek[i] );
    list.push_back( fk[i] );
  }
  for ( unsigned int i = 0; i < el.size(); ++i ) {

    list.push_back( el[i] );
    list.push_back( fl[i] );
  }

  return list;
}
