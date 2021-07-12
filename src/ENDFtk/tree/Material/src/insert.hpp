/**
 *  @brief Insert the section in the material
 *
 *  This function inserts the section in the ENDF material tree only if a
 *  section with that MT number is not present yet. If the file the section is
 *  to be added to is missing, it is added.
 *
 *  An exception will be thrown if the MAT number of the section does
 *  not match the MAT number of the file, and when a section with the
 *  same MT number is already present.
 *
 *  @param[in]   section   the section to be inserted
 */
void insert( Section&& section ) {

  if ( !this->hasMF( section.MF() ) ) {

    this->files_.emplace( section.MF(), File( this->MAT(), section.MF() ) );
  }

  this->MF( section.MF() ).insert( std::move( section ) );
}

/**
 *  @brief Insert the section in the material
 *
 *  This function inserts the section in the ENDF material tree only if a
 *  section with that MT number is not present yet. If the file the section is
 *  to be added to is missing, it is added.
 *
 *  An exception will be thrown if the MAT number of the section does
 *  not match the MAT number of the file, and when a section with the
 *  same MT number is already present.
 *
 *  @param[in]   section   the section to be inserted
 */
template< int MF, int... OptionalMT >
void insert( const section::Type< MF, OptionalMT... >& section ) {

  this->insert( toSection( section, this->MAT() ) );
}

/**
 *  @brief Insert the file in the material
 *
 *  This function inserts the file in the ENDF material tree only if a
 *  file with that MF number is not present yet.
 *
 *  An exception will be thrown if the MAT number of the file does
 *  not match the MAT number of the file, and when a file with the
 *  same MF number is already present.
 *
 *  @param[in]   file   the file to be inserted
 */
void insert( File&& file ) {

  if ( this->hasMF( file.MF() ) ) {

    Log::error( "A file for MF{} is already present in the ENDF material tree",
                file.MF() );
    throw std::exception();
  }

  this->insertOrReplace( std::move( file ) );
}
/**
 *  @brief Insert the file in the material
 *
 *  This function inserts the file in the ENDF material tree only if a
 *  file with that MF number is not present yet.
 *
 *  An exception will be thrown if the MAT number of the file does
 *  not match the MAT number of the file, and when a file with the
 *  same MF number is already present.
 *
 *  @param[in]   file   the file to be inserted
 */
template< int MF >
void insert( const file::Type< MF >& file ) {

  this->insert( toFile( file, this->MAT() ) );
}
