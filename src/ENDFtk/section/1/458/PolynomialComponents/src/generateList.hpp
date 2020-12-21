static std::vector< double >
generateList( std::vector< std::array< double, 2 > >&& efr,
              std::vector< std::array< double, 2 > >&& enp,
              std::vector< std::array< double, 2 > >&& end,
              std::vector< std::array< double, 2 > >&& egp,
              std::vector< std::array< double, 2 > >&& egd,
              std::vector< std::array< double, 2 > >&& eb,
              std::vector< std::array< double, 2 > >&& enu,
              std::vector< std::array< double, 2 > >&& er,
              std::vector< std::array< double, 2 > >&& et ) {

  std::vector< double > list;

  unsigned int size = efr.size();
  if ( ( enp.size() != size ) || ( end.size() != size ) ||
       ( egp.size() != size ) || ( egd.size() != size ) ||
       ( eb.size() != size ) || ( enu.size() != size ) ||
       ( er.size() != size ) || ( et.size() != size ) ) {

    Log::info( "The polynomial order each energy release component is not "
               "consistent" );
    Log::info( "NPLY value: {}", size - 1 );
    Log::info( "efr.size(): {}", efr.size() );
    Log::info( "enp.size(): {}", enp.size() );
    Log::info( "end.size(): {}", end.size() );
    Log::info( "egp.size(): {}", egp.size() );
    Log::info( "egd.size(): {}", egd.size() );
    Log::info( "eb.size(): {}", eb.size() );
    Log::info( "enu.size(): {}", enu.size() );
    Log::info( "er.size(): {}", er.size() );
    Log::info( "et.size(): {}", et.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < size; ++i ) {

    list.push_back( efr[i][0] );
    list.push_back( efr[i][1] );
    list.push_back( enp[i][0] );
    list.push_back( enp[i][1] );
    list.push_back( end[i][0] );
    list.push_back( end[i][1] );
    list.push_back( egp[i][0] );
    list.push_back( egp[i][1] );
    list.push_back( egd[i][0] );
    list.push_back( egd[i][1] );
    list.push_back( eb[i][0] );
    list.push_back( eb[i][1] );
    list.push_back( enu[i][0] );
    list.push_back( enu[i][1] );
    list.push_back( er[i][0] );
    list.push_back( er[i][1] );
    list.push_back( et[i][0] );
    list.push_back( et[i][1] );
  }
  return list;
}
