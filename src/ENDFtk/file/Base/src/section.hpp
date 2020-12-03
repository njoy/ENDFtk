/**
 *  @brief Retrieve a specific section
 *
 *  @param mt   the MT number of the section to be retrieved (e.g. 1_c)
 */
template< typename Index >
decltype( auto ) section( Index sectionNo ) const {

  try {

    return njoy::ENDFtk::details::get( this->derived().sectionMap[ sectionNo ] );
  }
  catch ( ... ) {

    int MF = this->derived().MF();
    Log::error( "Requested section number (MT) does not "
                "correspond to a stored section" );
    Log::info( "Requested section number: {}", sectionNo );
    Log::info( "File queried: {}", MF );

    throw std::out_of_range( "File " + std::to_string( MF ) + " section" );
  }
}

/**
 *  @brief Retrieve a specific section
 *
 *  @param mt   the MT number of the section to be retrieved (e.g. 1_c)
 */
template< typename Index >
decltype( auto ) section( Index sectionNo ) {

  decltype( auto ) section = const_cast< const Base* >( this )->derived().section( sectionNo );

  using Section_t =
    std::add_lvalue_reference_t< std::decay_t< decltype( section ) > >;

  return const_cast< Section_t >( section );
}
