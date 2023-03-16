/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in] mf   the MF number of the file to be returned
 */
const FileVariant& file( int mf ) const {

  try {

    return this->files_.at( mf );
  }
  catch( std::out_of_range& o ) {

    Log::error( "Requested file number (MF) does not"
                " correspond to a stored file" );
    Log::info( "Requested file number: {}", mf );
    Log::info( "Material queried: ", this->MAT() );
    throw o;
  }
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in] mf   the MF number of the file to be returned
 */
FileVariant& file( int mf ) {

  return const_cast< FileVariant& >(
      const_cast< const Material& >( *this ).file( mf ) );
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in] mf   the MF number of the file to be returned
 */
const FileVariant& MF( int mf ) const {

  return this->file( mf );
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in] mf   the MF number of the file to be returned
 */
FileVariant& MF( int mf ) {

  return this->file( mf );
}
