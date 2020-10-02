/**
 *  @brief Return the material with the requested MAT number
 *
 *  @param[in]   mat   the MAT number of the material to be returned
 */
auto material( int mat ) const {

  if ( not this->materials_.count( mat ) ) {

    Log::error( "Requested material number (MAT) does not"
                " correspond to a stored material syntax tree" );
    Log::info( "Requested material number: {}", mat );
    throw std::out_of_range( "Requested material number (MAT) does not"
                             " correspond to a stored material syntax tree" );
  }
  auto bounds = this->materials_.equal_range( mat );
  return
    ranges::make_iterator_range( bounds.first, bounds.second )
    | ranges::view::values;
}

/**
 *  @brief Return the material with the requested MAT number
 *
 *  @param[in]   mat   the MAT number of the material to be returned
 */
auto material( int mat ) {

  return
    static_cast< const Tape& >( *this ).material( mat )
    | ranges::view::transform
      ( []( const auto& material ) -> Material_t&
        { return const_cast< Material_t& >( material ); } );
}
