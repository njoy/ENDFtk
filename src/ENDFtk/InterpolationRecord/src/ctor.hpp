InterpolationRecord
( double C1, double C2, long L1, long L2,
  std::vector< long >&& boundaryIndices,
  std::vector< long >&& interpolationSchemeIndices )
  try :
    InterpolationBase( C1, C2, L1, L2,
                       std::move( boundaryIndices ),
                       std::move( interpolationSchemeIndices ) ) {}
  catch ( std::exception& e ) {
    Log::info( "Error encountered while constructing TAB2 record" );
    throw e;
  }

InterpolationRecord
( double C1, double C2, long L1, long L2,
  std::tuple< std::vector< long >, std::vector< long > >&& regions )
  try :
    InterpolationBase( C1, C2, L1, L2, std::move( regions ) ) {}
  catch ( std::exception& e ) {
    Log::info( "Error encountered while constructing TAB2 record" );
    throw e;
  }

template< typename Iterator >
InterpolationRecord
( Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT )
  try :
    InterpolationBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( IllegalN2& e ) {
    Log::error( "Illegal NZ value encountered" );
    Log::info( "NZ (or number of zones) must be greater than or equal to 1" );
    Log::info( "NZ value: {}", e.n2 );
    Log::info( "Error encountered while parsing TAB2 record" );
    throw std::exception();
  }
  catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing TAB2 record" );
    throw std::exception();
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while parsing TAB2 record" );
    throw e;
  }
