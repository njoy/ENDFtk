auto materialNumber( int materialNo ) const {
  if ( not materialMap.count( materialNo ) ){
    Log::error( "Requested material number (MAT) does not"
                " correspond to a stored material syntax tree" );
    Log::info( "Requested material number: {}", materialNo );
    throw std::out_of_range( "Requested material number (MAT) does not"
                             " correspond to a stored material syntax tree" );
  }
  auto bounds = this->materialMap.equal_range( materialNo );
  return
    ranges::make_iterator_range( bounds.first, bounds.second )
    | ranges::view::values
    | ranges::view::indirect;
}

auto materialNumber( int materialNo ) {
  return
    static_cast< const Tape& >( *this ).materialNumber( materialNo )
    | ranges::view::transform
      ( []( const auto& material ) -> Material_t&
        { return const_cast< Material_t& >( material ); } );
}
