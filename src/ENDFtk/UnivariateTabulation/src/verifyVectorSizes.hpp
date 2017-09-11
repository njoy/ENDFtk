static void
verifyVectorSizes( const std::vector< double >& xValues,
                   const std::vector< double >& yValues ) {
  const bool mismatchedEvaluationVectorLengths =
    ( xValues.size() != yValues.size() );
    
  if ( mismatchedEvaluationVectorLengths ) {
    Log::error( "Mismatched evaluation pair vector lengths" );
    Log::info( "X-values vector length: {}", xValues.size() );
    Log::info( "Y-values vector length: {}", yValues.size() );
    throw std::exception();
  }
}
