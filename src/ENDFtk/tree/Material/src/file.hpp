/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the material to be returned
 */
const File_t& file( int mf ) const {

  try {

    return this->files_.at( mf );
  }
  catch( std::out_of_range& o ) {

    Log::error
      ( "Requested file number (MF) does not"
        " correspond to a stored file syntax tree" );
    Log::info( "Requested file number: {}", mf );
    Log::info( "Material number of queried material syntax tree: ",
               this->materialNumber() );
    throw o;
  }
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the material to be returned
 */
File_t& file( int mf ) {

  return const_cast< File_t& >
         ( const_cast< const Material& >( *this ).file( mf ) );
}
