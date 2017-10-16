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
