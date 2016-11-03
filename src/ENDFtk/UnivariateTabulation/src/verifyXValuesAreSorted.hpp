static void
verifyXValuesAreSorted( const std::vector< double >& xValues ){
  auto xValuesIterator =
    std::is_sorted_until( xValues.begin(), xValues.end() );
    
  const bool xValuesAreSorted = ( xValuesIterator == xValues.end() );
    
  if ( not xValuesAreSorted ){
    LOG(ERROR) << "X-values are not sorted";
    const auto position = xValuesIterator - xValues.begin();
    LOG(INFO) << "X-value [" << (position - 1) << "]: "
              << xValuesIterator[-1];
    LOG(INFO) << "X-value [" << (position) << "]: " << xValuesIterator[0];
    throw std::exception();
  }
}
