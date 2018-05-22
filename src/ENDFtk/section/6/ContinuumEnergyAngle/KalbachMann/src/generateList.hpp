static std::vector< double >
generateList( std::vector< std::tuple< double, double, double > >&& data ) {

  std::vector< double > list;
  for ( unsigned int i = 0; i < data.size(); ++i ) {

    list.push_back( std::get< 0 >( data[i] ) );
    list.push_back( std::get< 1 >( data[i] ) );
    list.push_back( std::get< 2 >( data[i] ) );
  }
  return list;
}

static std::vector< double >
generateList( std::vector< std::tuple< double, double,
                                       double, double > >&& data ) {

  std::vector< double > list;
  for ( unsigned int i = 0; i < data.size(); ++i ) {

    list.push_back( std::get< 0 >( data[i] ) );
    list.push_back( std::get< 1 >( data[i] ) );
    list.push_back( std::get< 2 >( data[i] ) );
    list.push_back( std::get< 3 >( data[i] ) );
  }
  return list;
}
