template< long long int Index >
decltype(auto)
sectionNumber( hana::llong< Index > sectionNo ) const {
  try{
    return get( this->sectionMap[ sectionNo ] );
  } catch( ... ){
    Log::error( "Requested section number (MT) does not"
                " correspond to a stored section" );
    Log::info( "Requested section number: {}", sectionNo.value );
    Log::info( "File queried: ", 1 );
    throw std::out_of_range( "File 1 sectionNumber" );
  }
}

template< typename Index >
decltype(auto)
sectionNumber( Index sectionNo ) {
  decltype(auto) section =
    const_cast< const Type& >( *this ).sectionNumber( sectionNo );

  using Section_t =
    std::add_lvalue_reference_t< std::decay_t< decltype(section) > >;

  return const_cast< Section_t >( section );
}
