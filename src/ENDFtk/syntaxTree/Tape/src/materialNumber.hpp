Range
materialNumber( int materialNo ){
  if ( not materialMap.count( materialNo ) ){
    LOG(ERROR) << "Requested material number (MAT) does not"
               << " correspond to a stored material syntax tree";
    LOG(INFO)  << "Requested material number: " << materialNo;
    throw std::out_of_range( "Requested material number (MAT) does not"
                             " correspond to a stored material syntax tree" );
  }
  auto pairwiseIteratorBounds = materialMap.equal_range( materialNo );
  return Range( { MatchIterator( pairwiseIteratorBounds.first ),
                  MatchIterator( pairwiseIteratorBounds.second ) } );
}
