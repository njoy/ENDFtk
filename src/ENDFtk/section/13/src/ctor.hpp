template< typename Iterator >
Type ( HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: Base( head, MAT, 13 ),
       table( readTable( begin, end, lineNumber, 
                         head.MAT(), head.MT(), head.N1() ) ),
       subsections( readSubsections( begin, end, lineNumber, 
                                     head.MAT(), head.MT(), head.N1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 13 );
  } catch( std::exception& e ){
    Log::info
    ( "Encountered error while reading section {} of File 13 of Material {}",
      head.MT(), MAT );
    throw e;
  }

