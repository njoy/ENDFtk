template< typename Iterator >
Type ( const HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: 
    Base( head, MAT, 2 ),
    isotopes( readIsotopes( head, begin, end, lineNumber ) ) {
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section {} of File 2 of Material {}",
               head.MT(), MAT );
    throw e;
  }

