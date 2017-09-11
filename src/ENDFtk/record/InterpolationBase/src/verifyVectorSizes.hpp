static void
verifyVectorSizes( const std::vector< long >& boundaryIndices,
                   const std::vector< long >& interpolationSchemeIndices ) {
  const bool mismatchedRegionVectorLengths =
    ( boundaryIndices.size() != interpolationSchemeIndices.size() );

  if ( mismatchedRegionVectorLengths ) {
    Log::error( "Mismatched region pair vector lengths" );
    Log::info( "Boundary indices vector length: {}",
               boundaryIndices.size() );
    Log::info( "Interpolation scheme vector length: {}",
               interpolationSchemeIndices.size() );
    throw std::exception();
  }
}
