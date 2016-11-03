static void
verifyBoundaryIndicesAreSorted( const std::vector< long >& boundaryIndices ){
  auto boundaryIndexIterator = 
    std::is_sorted_until( boundaryIndices.begin(), boundaryIndices.end() );

  const bool boundariesAreSorted =
    ( boundaryIndexIterator == boundaryIndices.end() );
 
  if ( not boundariesAreSorted ){
    LOG(ERROR) << "Interpolation boundary indices are not sorted";
    const auto position = boundaryIndexIterator - boundaryIndices.begin();
    LOG(INFO) << "Boundary index [" << (position - 1) << "]: "
              << boundaryIndexIterator[-1];
    LOG(INFO) << "Boundary index [" << (position) << "]: "
              << boundaryIndexIterator[0];
    throw std::exception();
  }
}
