auto
rangeBoundaries( std::size_t rangeIndex ) const {
  if ( std::size_t(this->nRanges()) <= rangeIndex ){
    Log::error( "Out of range index requested of TAB1 record" );
    Log::info( "Requested index: {}", rangeIndex );
    Log::info( "Available index range: [ 0, {} )", this->boundaryIndices.size() );
    throw std::out_of_range("");
  }

  const std::size_t left = ( rangeIndex == 0  ) ? 0 :
                           this->boundaryIndices[ rangeIndex - 1 ] - 1;
  const std::size_t right = this->boundaryIndices[ rangeIndex ];
  return ranges::make_iterator_range( this->xBegin() + left,
				      this->xBegin() + right );
}
