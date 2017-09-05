InterpolationRecord
( double C1, double C2, long L1, long L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices ) :
  metadata( C1, C2, L1, L2, boundaryIndices.size(), boundaryIndices.back() ),
  boundaryIndices( std::move(boundaryIndices) ),
  interpolationSchemeIndices( std::move(interpolationSchemeIndices) ) {
  try{
    verifyBoundaryIndicesAreSorted( this->boundaryIndices );
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
  } catch( std::exception& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
    throw e; 
  }
}

InterpolationRecord
( double C1, double C2, long L1, long L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
  InterpolationRecord( C1, C2, L1, L2,
                       std::move( std::get<0>(regions) ),
                       std::move( std::get<1>(regions) ) ){}

InterpolationRecord
( Base&& metadata,
  std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
  InterpolationRecord( std::get<0>( metadata.fields ),
                       std::get<1>( metadata.fields ),
                       std::get<2>( metadata.fields ),
                       std::get<3>( metadata.fields ),
                       std::move( std::get<0>( regions ) ),
                       std::move( std::get<1>( regions ) ) ){}

protected:

template< typename Iterator >
InterpolationRecord
( Base&& metadata,
  Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) :
  InterpolationRecord( std::move( metadata ),
                       readRangeDescriptions( std::get<4>( metadata.fields ),
                                              it, end, lineNumber,
                                              MAT, MF, MT ) ) {}

public:

template< typename Iterator >
InterpolationRecord( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
  try:
    InterpolationRecord( readMetadata( it, end, lineNumber, MAT, MF, MT ),
                         it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ){
    Log::info( "Error encountered while parsing record" );
    throw e;
  } catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing record" );
    throw std::exception();
  }
