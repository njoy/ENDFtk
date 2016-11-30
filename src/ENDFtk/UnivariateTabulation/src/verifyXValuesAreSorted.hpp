static void
verifyXValuesAreSorted( const std::vector< double >& xValues ){
  auto xValuesIterator = std::is_sorted_until( xValues.begin(), xValues.end() );
  const bool xValuesAreSorted = ( xValuesIterator == xValues.end() );
    
  if ( not xValuesAreSorted ){
    Log::error( "X-values are not sorted" );
    const auto position = xValuesIterator - xValues.begin();
    Log::info( "X-value [{}]: {}", (position - 1), xValuesIterator[-1] );
    Log::info( "X-value [{}]: {}", position, xValuesIterator[0] );
    throw std::exception();
  }
}
