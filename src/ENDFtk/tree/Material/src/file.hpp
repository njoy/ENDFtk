/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the file to be returned
 */
const File& file( int mf ) const {

  auto iter = this->find( mf );
  if ( iter != this->files_.end() ) {

    return *iter;
  }

  Log::error( "The requested file (MF{}) is not present "
              "in the ENDF file tree", mf );
  throw std::exception();
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the file to be returned
 */
File& file( int mf ) {

  return const_cast< File& >
         ( const_cast< const Material& >( *this ).file( mf ) );
}
