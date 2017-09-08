UnivariateTabulation
( double C1, double C2, long L1, long L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices,
  std::vector< double >&& xValues,
  std::vector< double >&& yValues )
  try :
    InterpolationBase( C1, C2, L1, L2, std::move( boundaryIndices ),
                       std::move( interpolationSchemeIndices ) ),
    xValues( std::move(xValues) ),
    yValues( std::move(yValues) ) {
    verifyXValuesAreSorted( this->xValues );
    verifyVectorSizes( this->xValues, this->yValues );
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while constructing TAB1 record" );
    throw e;
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
( InterpolationBase&& interpolation,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  InterpolationBase( std::move( interpolation ) ),
  xValues( std::move( std::get<0>( points ) ) ),
  yValues( std::move( std::get<1>( points ) ) ) {}

template< typename Iterator >
UnivariateTabulation
( InterpolationBase&& interpolation,
  Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT  ) :
  UnivariateTabulation( std::move( interpolation ),
                        readPairs( interpolation.N2(), it, end, lineNumber, MAT, MF, MT ) ) {}

public:

template< typename Iterator >
UnivariateTabulation( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try: UnivariateTabulation( InterpolationBase( it, end, lineNumber, MAT, MF, MT ),
                             it, end, lineNumber, MAT, MF, MT ) {}
  catch ( IllegalN2& e ) {
    Log::error( "Illegal NP value encountered" );
    Log::info( "NP (or number of pairs) must be greater than or equal to 1" );
    Log::info( "NP value: {}", e.n2 );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( InconsistentN2& e ) {
    Log::error( "Inconsistent value for NP" );
    Log::info( "Expected {} as the largest index but found {}", e.n2, e.index );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while parsing TAB1 record" );
    throw e;
  }
