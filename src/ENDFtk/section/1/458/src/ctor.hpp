template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 1 ),
       lfc_( head.L2() ),
       nfc_( head.N2() ),
       data_( readFissionEnergyReleaseData( begin, end, lineNumber, MAT,
                                            head.L2(), head.N2() ) ) {
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 458 of File 1 of Material {}", MAT );
    throw e;
  }

