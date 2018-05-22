static std::vector< double >
generateList( unsigned int na, 
              std::vector< std::pair< double ,
                                      std::vector< double > > >&& data ) {

  std::vector< double > list;
  for ( unsigned int i = 0; i < data.size(); ++i ) {

    if ( 1 + na != data[i].second.size() ) {

      Log::error( "The number of coefficients for each energy value must "
                  "be the same" );
      Log::info( "Expected: {}", 1 + na );
      Log::info( "Found: {}", data[i].second.size() );
      Log::info( "Energy: {}", data[i].first );
      throw std::exception();
    }

    list.insert( list.end(), data[i].first );
    list.insert( list.end(), data[i].second.begin(), data[i].second.end() );
  }
  return list;
}
