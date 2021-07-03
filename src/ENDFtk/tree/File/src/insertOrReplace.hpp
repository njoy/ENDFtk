/**
 *  @brief Insert or replace the section in the file
 *
 *  This function inserts or replaces the section in the ENDF file tree.
 *
 *  An exception will be thrown is the MAT and MF number of the section do
 *  not match the MAT and MF number of the file.
 *
 *  @param[in]   section   the section to be inserted or replaced
 */
void insertOrReplace( Section&& section ) {

  if ( ( this->MAT() != section.MAT() ) || ( this->MF() != section.MF() ) ) {

    Log::error( "The section to be inserted does not have the correct "
                "MAT and MF number" );
    Log::info( "Expected MAT{} MF{}", this->MAT(), this->MF() );
    Log::info( "Found MAT{} MF{}", section.MAT(), section.MF() );
    throw std::exception();
  }

  auto iter = this->sections_.find( section.MT() );
  if ( iter != this->sections_.end() ) {

    this->sections_.erase( iter );
  }
  this->sections_.emplace( section.MT(), std::move( section ) );
}
