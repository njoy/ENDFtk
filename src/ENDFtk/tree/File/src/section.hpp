/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MT number of the section to be returned
 */
const Section_t& section( int mt ) const {

  try {

    return this->sections_.at( mt );
  }
  catch( std::out_of_range& o ) {

    Log::error( "Requested section number (MT) does not"
                " correspond to a stored section in the syntax tree" );
    Log::info( "Requested section number: {}", mt );
    Log::info( "File number of queried file syntax tree: {}",
               this->fileNumber() );
    throw o;
  }
}

/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MT number of the section to be returned
 */
Section_t& section( int mt ) {
  return const_cast< Section_t& >
         ( const_cast< const File& >( *this ).section( mt ) );
}
