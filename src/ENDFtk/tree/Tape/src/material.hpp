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
                             " correspond to a stored material tree" );
  }
  auto bounds = this->materials_.equal_range( mat );
  return
    ranges::make_subrange( bounds.first, bounds.second )
    | ranges::cpp20::views::values;
}

/**
 *  @brief Return the material with the requested MAT number
 *
 *  @param[in]   mat   the MAT number of the material to be returned
 */
auto material( int mat ) {

  return
    static_cast< const Tape& >( *this ).material( mat )
    | ranges::cpp20::views::transform
      ( [] ( const auto& material ) -> Material&
           { return const_cast< Material& >( material ); } );
}
