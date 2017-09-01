template< typename Iterator >
DataType ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ), data_( head, begin, end, lineNumber, MAT, 1, 458 ) ) {
      readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", 458, MAT );
    throw e;
  }

