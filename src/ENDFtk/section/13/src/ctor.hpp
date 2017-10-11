template< typename Iterator >
Type ( HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: Base( head, MAT, 13 ),
       table( readTable( begin, end, lineNumber, head.MAT(), head.MT() ) ){ 
    readSEND(begin, end, lineNumber, MAT, 3 );
  } catch( std::exception& e ){
    Log::info
    ( "Encountered error while reading section {} of file 13 of material {}",
      head.MT(), MAT );
    throw e;
  }

