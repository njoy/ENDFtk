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

  auto fill = [] ( const auto& component, auto& values ) {

    for ( auto&& entry : component ) {

      values.push_back( entry[0] );
      values.push_back( entry[1] );
    }
  };

  fill( efr, list );
  fill( enp, list );
  fill( end, list );
  fill( egp, list );
  fill( egd, list );
  fill( eb, list );
  fill( enu, list );
  fill( er, list );
  fill( et, list );

  return list;
}

static std::vector< double >
generateList( const ListRecord& list ) {

  std::vector< double > values;

  int npl = list.NPL();
  int nply =  list.L2();
  if ( npl != ( nply + 1 ) * 18 ) {

    Log::error( "Encountered illegal NPL value" );
    Log::info( "NPL must be equal to {}", ( nply + 1 ) * 18 );
    Log::info( "NPL value: {}", npl );
    throw std::exception();
  }

  for ( std::size_t j = 0; j < 9; ++j ) {

    for ( std::size_t i = 0; i < nply + 1; ++i ) {

      values.push_back( list.list()[ i * 18 + j * 2 ] );
      values.push_back( list.list()[ i * 18 + j * 2 + 1 ] );
    }
  }
  return values;
}
