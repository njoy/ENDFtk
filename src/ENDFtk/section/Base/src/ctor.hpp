Base( int MT, double zaid, double awr ) :
  sectionNo( MT ), ZA_( zaid ), atomicWeightRatio_( awr ) {}

Base( const HEAD& head, int MAT, int MF ) :
  sectionNo( head.MT() ), 
  ZA_( head.ZA() ), 
  atomicWeightRatio_( head.atomicWeightRatio() ) { 
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
