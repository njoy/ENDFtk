/**
 *  @brief Insert the section in the file
 *
 *  This function inserts the section in the ENDF file tree only if a
 *  section with that MT number is not present yet.
 *
 *  An exception will be thrown is the MAT and MF number of the section do
 *  not match the MAT and MF number of the file, and when a section with the
 *  same MT number is already present.
 *
 *  @param[in]   section   the section to be inserted
 */
void insert( Section&& section ) {

  if ( this->hasMT( section.MT() ) ) {

    Log::error( "A section for MT{} is already present in the ENDF file tree",
                section.MT() );
    throw std::exception();
  }

  this->insertOrReplace( std::move( section ) );
}
