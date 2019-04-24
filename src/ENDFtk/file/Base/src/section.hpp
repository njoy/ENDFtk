/**
 *  @brief Retrieve a specific MT section
 *
 *  @param mt   the MT number of the section to be retrieved (e.g. 451_c)
 */
template< typename Index >
decltype( auto ) section( Index sectionNo ) const {

  try {

    return get( static_cast< const Derived* >( this )->sectionMap[ sectionNo ] );
  }
  catch ( ... ) {

    int MF = static_cast< const Derived* >( this )->MF();
    Log::error( "Requested section number (MT) does not "
                "correspond to a stored section" );
    Log::info( "Requested section number: {}", sectionNo );
    Log::info( "File queried: {}", MF );

    throw std::out_of_range( "File " + std::to_string( MF ) + " sectionNumber" );
  }
}

/**
 *  @brief Retrieve a specific MT section
 *
 *  @param mt   the MT number of the section to be retrieved (e.g. 451_c)
 */
template< typename Index >
decltype( auto ) section( Index sectionNo ) {

  decltype( auto ) section =
    static_cast< const Derived& >( *this ).section( sectionNo );

  using Section_t =
    std::add_lvalue_reference_t< std::decay_t< decltype( section ) > >;

  return const_cast< Section_t >( section );
}
