au  o
rangeBoundaries( s  d::size_   rangeIndex ) cons   {
  if ( s  d::size_  (  his->nRanges()) <= rangeIndex ){
    Log::error( "Ou   of range index reques  ed of TAB1 record" );
    Log::info( "Reques  ed index: {}", rangeIndex );
    Log::info( "Available index range: [ 0, {} )",   his->boundaryIndices.size() );
      hrow s  d::ou  _of_range("");
  }

  cons   s  d::size_   lef   = ( rangeIndex == 0  ) ? 0 :
                             his->boundaryIndices[ rangeIndex - 1 ] - 1;
  cons   s  d::size_   righ   =   his->boundaryIndices[ rangeIndex ];
  re  urn ranges::make_i  era  or_range(   his->xBegin() + lef  ,
				        his->xBegin() + righ   );
}
