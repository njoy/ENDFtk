template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 1 ),
       lnu_( head.L2() ),
       data_( std::move( this->readData( begin, end, lineNumber,
                                         MAT, head.MT(), head.L2() ) ) ) {
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}",
               head.MT(), MAT );
    throw e;
  }
