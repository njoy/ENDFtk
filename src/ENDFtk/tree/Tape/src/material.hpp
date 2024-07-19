/**
 *  @brief Return the materials with the requested MAT number
 *
 *  This function returns a range of materials since a tape can contain
 *  multiple instances of the same material (e.g. at different
 *  temperatures).
 *
 *  @param[in]   mat   the MAT number of the material to be returned
 */
auto material( int mat ) const {

  auto range = this->find( mat );
  if ( range.first ==  range.second ) {

    Log::error( "Requested material number (MAT) does not"
                " correspond to a stored material syntax tree" );
    Log::info( "Requested material number: {}", mat );
    throw std::out_of_range( "Requested material number (MAT) does not"
                             " correspond to a stored material tree" );
  }
  return
    ranges::make_subrange( range.first, range.second )
    | ranges::cpp20::views::all;
}

/**
 *  @brief Return the materials with the requested MAT number
 *
 *  This function returns a range of materials since a tape can contain
 *  multiple instances of the same material (e.g. at different
 *  temperatures).
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
