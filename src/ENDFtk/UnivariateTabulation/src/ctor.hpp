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
      (this->boundaryIndices.size() != this->interpolationSchemeIndices.size());
    if ( mismatchedRegionVectorLengths ){
      LOG(ERROR) << "Mismatched region pair vector lengths";
      LOG(INFO) << "Boundary indices vector length: "
                << this->boundaryIndices.size();
      LOG(INFO) << "Interpolation scheme vector length: "
                << this->interpolationSchemeIndices.size();
      throw std::exception();
    }
    const bool mismatchedEvaluationVectorLengths =
      ( this->xValues.size() != this->yValues.size() );
    if ( mismatchedEvaluationVectorLengths ){
      LOG(ERROR) << "Mismatched evaluation pair vector lengths";
      LOG(INFO) << "X-values vector length: "
                << this->xValues.size();
      LOG(INFO) << "Y-values vector length: "
                << this->yValues.size();
      throw std::exception();
    }
  } catch( std::exception& e ){
    LOG(INFO) << "Error while reading TAB1 ordered pairs";
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
    LOG(INFO) << "Error encountered while parsing Tab1 record";
    throw e;
  } catch ( int nPosition ){
    LOG(INFO) << "Error in position " << nPosition;
    LOG(INFO) << "Error encountered while parsing Tab1 record";
    throw std::exception();
  }
