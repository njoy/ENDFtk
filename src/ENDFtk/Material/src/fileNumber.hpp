template< int Index >
decltype(auto)
fileNumber( hana::int_< Index > fileNo ) const {
  try{
    return get( this->fileMap[ fileNo ] );
  } catch( ... ){
    Log::error( "Requested file number (MF) does not"
                " correspond to a stored file" );
    Log::info( "Requested file number: {}", fileNo.value );
    Log::info( "Material queried: ",  );
    throw std::out_of_range( "Material file query" );
  }
}

template< typename Index >
decltype(auto)
fileNumber( Index fileNo ){
  decltype(auto) file =
    const_cast< const Type& >( *this ).fileNumber( sectionNo );

  using File_t =
    std::add_lvalue_reference_t< std::decay_t< decltype(file) > >;

  return const_cast< File_t >( file );
}
