/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MT number of the section to be returned
 */
const Section& section( int mt ) const {

  auto iter = this->find( mt );
  if ( iter != this->sections_.end() ) {

    return *iter;
  }

  Log::error( "The requested section (MF{} MT{}) is not present "
              "in the ENDF file tree",
              this->fileNumber(), mt );
  throw std::exception();
}

/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MF number of the section to be returned
 */
Section& section( int mt ) {

  return const_cast< Section& >
         ( const_cast< const File& >( *this ).section( mt ) );
}
