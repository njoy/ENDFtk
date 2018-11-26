static std::vector< double >
generateList( unsigned int na, 
              std::vector< std::pair< double ,
                                      std::vector< double > > >&& data ) {

  std::vector< double > list;
  for ( auto& entry : data ) {

    if ( 1 + na != entry.second.size() ) {

      Log::error( "The number of coefficients for each energy value must "
                  "be the same" );
      Log::info( "Expected: {}", 1 + na );
      Log::info( "Found: {}", entry.second.size() );
      Log::info( "Energy: {}", entry.first );
      throw std::exception();
    }

    list.insert( list.end(), entry.first );
    list.insert( list.end(), entry.second.begin(), entry.second.end() );
  }
  return list;
}
