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
