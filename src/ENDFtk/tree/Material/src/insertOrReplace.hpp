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
