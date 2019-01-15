Type( int MT, double zaid, double awr, double qm, double qi, long lr,
      std::vector< long >&& boundaries, std::vector< long >&& interpolants,
      std::vector< double >&& energies, std::vector< double >&& xs ) :
  Base( zaid, awr, MT ),
  table( qm, qi, 0, lr,
         std::move( boundaries ), std::move( interpolants ),
         std::move( energies ), std::move( xs ) ) {}

template< typename Iterator >
Type ( HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: Base( head, MAT, 3 ),
       table( begin, end, lineNumber, head.MAT(), 3, head.MT() ){ 
    readSEND(begin, end, lineNumber, MAT, 3 );
  } catch( std::exception& e ){
    Log::info
    ( "Encountered error while reading section {} of file 3 of material {}",
      head.MT(), MAT );
    throw e;
  }
