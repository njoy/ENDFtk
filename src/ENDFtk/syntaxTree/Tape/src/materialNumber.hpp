Range
materialNumber( int materialNo ){
  if ( not materialMap.count( materialNo ) ){
    Log::error( "Requested material number (MAT) does not"
                " correspond to a stored material syntax tree" );
    Log::info( "Requested material number: {}", materialNo );
    throw std::out_of_range( "Requested material number (MAT) does not"
                             " correspond to a stored material syntax tree" );
  }
  auto pairwiseIteratorBounds = this->materialMap.equal_range( materialNo );
  auto first = MatchIterator( pairwiseIteratorBounds.first );
  auto second = MatchIterator( pairwiseIteratorBounds.second );
  return Range( std::make_pair( first, second ) );
}
