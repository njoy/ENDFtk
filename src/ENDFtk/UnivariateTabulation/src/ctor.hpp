UnivariateTabulation
( double C1, double C2, long L1, long L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices,
  std::vector< double >&& xValues,
  std::vector< double >&& yValues ) :
  InterpolationRecord( C1, C2, L1, L2, std::move( boundaryIndices ), std::move( interpolationSchemeIndices ) ),
  xValues( std::move(xValues) ),
  yValues( std::move(yValues) ) {
  try{
    verifyXValuesAreSorted( this->xValues );
    const bool mismatchedEvaluationVectorLengths =
      ( this->xValues.size() != this->yValues.size() );
    if ( mismatchedEvaluationVectorLengths ){
      Log::error( "Mismatched evaluation pair vector lengths" );
      Log::info( "X-values vector length: {}",
                 this->xValues.size() );
      Log::info( "Y-values vector length: {}",
                 this->yValues.size() );
      throw std::exception();
    }
  } catch( std::exception& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
    throw e; 
  }
}

UnivariateTabulation
( double C1, double C2, long L1, long L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regions,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  UnivariateTabulation( C1, C2, L1, L2,
                        std::move( std::get<0>(regions) ),
                        std::move( std::get<1>(regions) ),
                        std::move( std::get<0>(points) ),
                        std::move( std::get<1>(points) ) ){}

protected:

UnivariateTabulation
( InterpolationRecord&& interpolation,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  InterpolationRecord( std::move( interpolation ) ),
  xValues( std::move( std::get<0>( points ) ) ),
  yValues( std::move( std::get<1>( points ) ) ) {}

template< typename Iterator >
UnivariateTabulation
( InterpolationRecord&& interpolation,
  Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT  ) :
  UnivariateTabulation( std::move( interpolation ),
                        readPairs( interpolation.NZ(), it, end, lineNumber, MAT, MF, MT ) ) {}

public:

template< typename Iterator >
UnivariateTabulation( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try: UnivariateTabulation( InterpolationRecord( it, end, lineNumber, MAT, MF, MT ),
                             it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ){
    Log::info( "Error encountered while parsing Tab1 record" );
    throw e;
  } catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing Tab1 record" );
    throw std::exception();
  }
