UnivariateTabulation()
  try:
    metadata( 0.0, 0.0, 0, 0, 0, 0 ),
    regionPairs( std::make_tuple( std::vector<long>(), std::vector<long>() ) ),
    evaluationPairs( std::make_tuple( std::vector<double>(), 
                                     std::vector<double>() ) )
  {
  } catch( std::exception& e ){
    Log::info( "Error default constructing Tab1 Record." );
    throw std::exception();
  }

UnivariateTabulation
( double C1, double C2, uint64_t L1, uint64_t L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regionPairs,
  std::tuple< std::vector< double >,
  std::vector< double > >&& evaluationPairs ) :
  metadata( C1, C2, L1, L2,
            std::get< 0 >( regionPairs ).size(),
            std::get< 0 >( evaluationPairs ).size() ),
  regionPairs( std::move( regionPairs ) ),
  evaluationPairs( std::move( evaluationPairs ) ) {
  try{
    verifyBoundaryIndicesAreSorted( this->boundaryIndices );
    verifyXValuesAreSorted( this->xValues );
    const bool mismatchedRegionVectorLengths =
      ( this->boundaryIndices.size()
	!= this->interpolationSchemeIndices.size() );
    if ( mismatchedRegionVectorLengths ){
      Log::error( "Mismatched region pair vector lengths" );
      Log::info( "Boundary indices vector length: {}",
		 this->boundaryIndices.size() );
      Log::info( "Interpolation scheme vector length: {}",
		 this->interpolationSchemeIndices.size() );
      throw std::exception();
    }
    const bool mismatchedEvaluationVectorLengths =
      ( this->xValues.size() != this->yValues.size() );
    if ( mismatchedEvaluationVectorLengths ){
      Log::error( "Mismatched evaluation pair vector lengths" );
      Log::info( "X-values vector length: {}",
		 this->xValues.size() );
      Log::info( "Y-values vector length: ",
                 this->yValues.size() );
      throw std::exception();
    }
  } catch( std::exception& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
    throw e; 
  }
}

template< typename Iterator >
UnivariateTabulation( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try: metadata( readMetadata( it, end, lineNumber, MAT, MF, MT ) ),
         regionPairs(
           readRangeDescriptions
           ( std::get<4>( this->metadata.fields ), it, end, lineNumber, MAT, MF, MT ) ),
         evaluationPairs(
           readPairs
           ( std::get<5>( this->metadata.fields ), it, end, lineNumber, MAT, MF, MT ) ){
       } catch ( std::exception& e ){
    Log::info( "Error encountered while parsing Tab1 record" );
    throw e;
  } catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing Tab1 record" );
    throw std::exception();
  }
