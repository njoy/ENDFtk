template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 1 ),
       data_( std::move( readPhotonData( begin, end, lineNumber,
                                         MAT, head.L1(), head.N1() ) ) ) {
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 460 of File 1 of Material {}", MAT );
    throw e;
  }

