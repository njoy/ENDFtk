/**
 *  @brief Retrieve a specific file
 *
 *  @param mf   the MF number of the file to be retrieved (e.g. 1_c)
 */
template< typename Index >
decltype( auto ) file( Index mf ) const {

  try {

    return details::get( this->fileMap[ mf ] );
  }
  catch ( ... ) {

    int MAT = this->MAT();
    Log::error( "Requested file number (MF) does not "
                "correspond to a stored file" );
    Log::info( "Requested file number: {}", mf );
    Log::info( "Material queried: {}", MAT );

    throw std::out_of_range( "Material " + std::to_string( MAT ) + " file" );
  }
}

/**
 *  @brief Retrieve a specific file
 *
 *  @param mf   the MF number of the file to be retrieved (e.g. 1_c)
 */
template< typename Index >
decltype( auto ) file( Index mf ) {

  decltype( auto ) file = const_cast< const Material& >( *this ).file( mf );

  using File_t =
    std::add_lvalue_reference_t< std::decay_t< decltype( file ) > >;

  return const_cast< File_t >( file );
}
