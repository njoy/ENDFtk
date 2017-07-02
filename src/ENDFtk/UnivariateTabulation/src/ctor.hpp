UnivariateTabulation
( double C1, double C2, uint64_t L1, uint64_t L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices,
  std::vector< double >&& xValues,
  std::vector< double >&& yValues ) :
  metadata( C1, C2, L1, L2, boundaryIndices.size(), xValues.size() ),
  boundaryIndices( std::move(boundaryIndices) ),
  interpolationSchemeIndices( std::move(interpolationSchemeIndices) ),
  xValues( std::move(xValues) ),
  yValues( std::move(yValues) ) {
  try{
    verifyBoundaryIndicesAreSorted( this->boundaryIndices );
    verifyXValuesAreSorted( this->xValues );
    const bool mismatchedRegionVectorLengths =
      ( this->boundaryIndices.size() != this->interpolationSchemeIndices.size() );
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
( double C1, double C2, uint64_t L1, uint64_t L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regions,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  UnivariateTabulation( C1, C2, L1, L2,
			std::move( std::get<0>(regions) ),
			std::move( std::get<1>(regions) ),
			std::move( std::get<0>(points) ),
			std::move( std::get<1>(points) ) ){}

UnivariateTabulation
( Base&& metadata,
  std::tuple< std::vector< long >, std::vector< long > >&& regions,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  UnivariateTabulation( std::get<0>(metadata.fields),
			std::get<1>(metadata.fields),
			std::get<2>(metadata.fields),
			std::get<3>(metadata.fields),
			std::move( std::get<0>(regions) ),
			std::move( std::get<1>(regions) ),
			std::move( std::get<0>(points) ),
			std::move( std::get<1>(points) ) ){}

protected:

template< typename Iterator >
UnivariateTabulation
( Base&& metadata,
  std::tuple< std::vector< long >, std::vector< long > >&& regions,
  Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) :
  UnivariateTabulation( std::move( metadata ),
                        std::move( regions ),
			readPairs( std::get<5>( metadata.fields ),
				   it, end, lineNumber, MAT, MF, MT ) ){}

template< typename Iterator >
UnivariateTabulation
( Base&& metadata,
  Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) :
  UnivariateTabulation( std::move( metadata ),
			readRangeDescriptions( std::get<4>( metadata.fields ),
					       it, end, lineNumber,
                                               MAT, MF, MT ),
                        it, end, lineNumber, MAT, MF, MT ) {}

public:

template< typename Iterator >
UnivariateTabulation( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try:
    UnivariateTabulation( readMetadata( it, end, lineNumber, MAT, MF, MT ),
			  it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ){
    Log::info( "Error encountered while parsing Tab1 record" );
    throw e;
  } catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing Tab1 record" );
    throw std::exception();
  }
