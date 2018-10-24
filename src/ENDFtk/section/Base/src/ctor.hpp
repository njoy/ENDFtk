Base( double ZA, double AWR, int MT ) :
  sectionNo( MT ),
  ZA_( ZA ),
  atomicWeightRatio_( AWR ) {
  if ( MT < 1 ){
    Log::error( "Illegal section number" );
    Log::info( "Section (MT) numbers must be greater than zero" );
    Log::info( "Encountered section number: {}", MT );
    throw std::runtime_error("section::Base ctor");
  }
  if ( ZA < 1 ){
    Log::error( "Illegal ZA number" );
    Log::info( "ZA numbers must be greater than zero" );
    Log::info( "Encountered ZA number: {}", ZA );
    throw std::runtime_error("section::Base ctor");
  }
  if ( AWR < 0.0 ){
    Log::error( "Illegal atomic mass ratio" );
    Log::info( "atomic mass ratio numbers must be greater than zero" );
    Log::info( "Encountered atomic mass ratio: {}", AWR );
    throw std::runtime_error("section::Base ctor");
  }
}

Base( const HEAD& head, int MAT, int MF ) :
  Base( head.ZA(), head.atomicWeightRatio(), head.MT() ){
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
