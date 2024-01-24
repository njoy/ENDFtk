//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Base() = default;
#endif

Base( int ZA, double AWR, int MT ) :
  BaseWithoutMT( ZA, AWR ), MT_( MT ) {

  if ( MT < 1 ) {

    Log::error( "Illegal section number" );
    Log::info( "Section (MT) numbers must be greater than zero" );
    Log::info( "Encountered section number: {}", MT );
    throw std::exception();
  }
}

Base( const HEAD& head, int MAT, int MF ) :
  Base( head.ZA(), head.atomicWeightRatio(), head.MT() ) {
    
  if ( MAT != head.MAT() ) {

    Log::error( "Incorrect Material number (MAT)." );
    Log::info( "Expected MAT = {}", MAT );
    Log::info( "Encountered MAT = {}", head.MAT() );
    throw std::exception();
  }
  if ( MF != head.MF() ) {

    Log::error( "Incorrect File number (MF)." );
    Log::info( "Expected MF = {}", MF );
    Log::info( "Encountered MF = {}", head.MF() );
    throw std::exception();
  }
}
