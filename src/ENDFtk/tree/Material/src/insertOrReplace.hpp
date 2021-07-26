/**
 *  @brief Insert or replace the section in the material
 *
 *  This function inserts or replaces the section in the ENDF material tree.
 *
 *  An exception will be thrown if the MAT number of the section does
 *  not match the MAT number of the material.
 *
 *  @param[in]   section   the section to be inserted or replaced
 */
void insertOrReplace( Section&& section ) {

  if ( !this->hasMF( section.MF() ) ) {

    this->files_.emplace( section.MF(), File( this->MAT(), section.MF() ) );
  }

  this->MF( section.MF() ).insertOrReplace( std::move( section ) );
}

/**
 *  @brief Insert or replace the section in the material
 *
 *  This function inserts or replaces the section in the ENDF material tree.
 *
 *  An exception will be thrown if the MAT number of the section does
 *  not match the MAT number of the material.
 *
 *  @param[in]   section   the section to be inserted or replaced
 */
template< int MF, int... OptionalMT >
void insertOrReplace( const section::Type< MF, OptionalMT... >& file ) {

  this->insertOrReplace( toSection( file, this->MAT() ) );
}

/**
 *  @brief Insert or replace the file in the material
 *
 *  This function inserts or replaces the file in the ENDF material tree. This
 *  does not merge sections if the file is already present: the old file is
 *  removed prior to inserting the new file.
 *
 *  An exception will be thrown if the MAT number of the file does
 *  not match the MAT number of the material.
 *
 *  @param[in]   file   the file to be inserted or replaced
 */
void insertOrReplace( File&& file ) {

  if ( this->MAT() != file.MAT() ) {

    Log::error( "The file to be inserted does not have the correct "
                "MAT number" );
    Log::info( "Expected MAT{}", this->MAT() );
    Log::info( "Found MAT{}", file.MAT() );
    throw std::exception();
  }

  this->remove( file.MF() );
  this->files_.emplace( file.MF(), std::move( file ) );
}

/**
 *  @brief Insert or replace the file in the material
 *
 *  This function inserts or replaces the file in the ENDF material tree. This
 *  does not merge sections if the file is already present: the old file is
 *  removed prior to inserting the new file.
 *
 *  An exception will be thrown if the MAT number of the file does
 *  not match the MAT number of the material.
 *
 *  @param[in]   file   the file to be inserted or replaced
 */
template< int MF >
void insertOrReplace( const file::Type< MF >& file ) {

  this->insertOrReplace( toFile( file, this->MAT() ) );
}
