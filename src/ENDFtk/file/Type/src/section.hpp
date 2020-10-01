/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in] mt   the MT number of the section to be returned
 */
const Section& section( int mt ) const {

  try {

    return this->sectionMap.at( sectionNo );
  }
  catch( std::out_of_range& o ) {

    Log::error( "Requested section number (MT) does not"
                " correspond to a stored section" );
    Log::info( "Requested section number: {}", sectionNo );
    Log::info( "File queried: ", this->MF() );
    throw o;
  }
}

/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in] mt   the MT number of the section to be returned
 */
Section& section( int sectionNo ) {

  return const_cast< Section& >(
      const_cast< const Type& >( *this ).section( sectionNo ) );
}
