static void
verifyXValuesAreSorted( const std::vector< double >& xValues ){
  auto xValuesIterator = std::is_sorted_until( xValues.begin(), xValues.end(),
    []( auto&& rhs, auto&& lhs ){ return lhs > rhs; }
                                               );
  if ( xValuesIterator != xValues.end() ){
    Log::error( "X-values are not sorted" );
    const auto position = xValuesIterator - xValues.begin();
    Log::info( "X-value [{}]: {:.16E}", (position - 1), xValuesIterator[-1] );
    Log::info( "X-value [{}]: {:.16E}", position, xValuesIterator[0] );
    throw std::exception();
  }
}
