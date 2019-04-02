InterpolationBase
( double C1, double C2, long L1, long L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices ) :
  metadata( C1, C2, L1, L2, boundaryIndices.size(), boundaryIndices.back() ),
  boundaryIndices( std::move(boundaryIndices) ),
  interpolationSchemeIndices( std::move(interpolationSchemeIndices) ) {
  verifyVectorSizes( this->boundaryIndices, this->interpolationSchemeIndices );
  verifyBoundaryIndicesAreSorted( this->boundaryIndices );
}

InterpolationBase
( double C1, double C2, long L1, long L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
  InterpolationBase( C1, C2, L1, L2,
                     std::move( std::get<0>(regions) ),
                     std::move( std::get<1>(regions) ) ) {}

protected:

InterpolationBase
( Base&& metadata,
  std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
  InterpolationBase( std::get<0>( metadata.fields ),
                     std::get<1>( metadata.fields ),
                     std::get<2>( metadata.fields ),
                     std::get<3>( metadata.fields ),
                     std::move( std::get<0>( regions ) ),
                     std::move( std::get<1>( regions ) ) ) {
  verifyN2( std::get<5>( metadata.fields ), this->boundaryIndices.back() );
}

template< typename Iterator >
InterpolationBase
( Base&& metadata,
  Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) :
  InterpolationBase( std::move( metadata ),
                     readRangeDescriptions( std::get<4>( metadata.fields ),
                                              it, end, lineNumber,
                                              MAT, MF, MT ) ) {}

public:

template< typename Iterator >
InterpolationBase
( Iterator& it, const Iterator& end, long& lineNumber,
 int MAT, int MF, int MT ) :
 InterpolationBase( readMetadata( it, end, lineNumber, MAT, MF, MT ),
                    it, end, lineNumber, MAT, MF, MT ) {}
