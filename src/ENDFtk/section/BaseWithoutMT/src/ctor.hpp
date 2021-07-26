//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
BaseWithoutMT() = default;
#endif

BaseWithoutMT( double ZA, double AWR ) :
  ZA_( ZA ),
  atomicWeightRatio_( AWR ) {
  if ( ZA < 1 ){
    Log::error( "Illegal ZA number" );
    Log::info( "ZA numbers must be greater than zero" );
    Log::info( "Encountered ZA number: {}", ZA );
    throw std::exception();
  }
  if ( AWR < 0.0 ){
    Log::error( "Illegal atomic mass ratio" );
    Log::info( "atomic mass ratio numbers must be greater than zero" );
    Log::info( "Encountered atomic mass ratio: {}", AWR );
    throw std::exception();
  }
}

BaseWithoutMT( const HEAD& head, int MAT, int MF ) :
  BaseWithoutMT( head.ZA(), head.atomicWeightRatio() ){
  if( MAT != head.MAT() ){
    Log::error( "Incorrect Material number (MAT)." );
    Log::info( "Expected MAT = {}", MAT );
    Log::info( "Encountered MAT = {}", head.MAT() );
    throw std::exception();
  }
  if( MF != head.MF() ){
    Log::error( "Incorrect File number (MF)." );
    Log::info( "Expected MF = {}", MF );
    Log::info( "Encountered MF = {}", head.MF() );
    throw std::exception();
  }
}
