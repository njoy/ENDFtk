template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 1 ),
       lambda_( std::move( nubar::readDecayConstantData( begin, end, lineNumber,
                                                         MAT, 1, 455, head.L1() ) ) ),
       nubar_( std::move( readNubarData( begin, end, lineNumber,
                                         MAT, 1, 455, head.L2() ) ) ) {
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 455 of File 1 of Material {}",
               MAT );
    throw e;
  }
