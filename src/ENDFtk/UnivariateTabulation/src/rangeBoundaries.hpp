std::tuple< constXIterator, constXIterator >
rangeBoundaries( std::size_t rangeIndex ) const {
  if ( std::size_t(this->nRanges()) <= rangeIndex ){
    Log::error( "Out of range range index requested of TAB1 record" );
    Log::info( "Requested index: {}", rangeIndex );
    Log::info( "Available index range: [ 0, {} )",
	       this->boundaryIndices.size() );
    throw std::out_of_range("");
  }
  const bool isFirstRange = ( rangeIndex == 0 );
  const std::size_t right = this->boundaryIndices[ rangeIndex-- ];
  const std::size_t
    left = ( isFirstRange ) ? 0 : this->boundaryIndices[ rangeIndex ] - 1;
  return std::make_tuple( this->xBegin() + left, this->xBegin() + right );
}
