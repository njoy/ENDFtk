template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 1 ),
       lfc_( verifyLFC( head.L2() ) ),
       components_( begin, end, lineNumber, MAT, 1, 458 ),
       tables_( readTables( begin, end, lineNumber, MAT, verifyNFC( head.N2() ) ) ) {
    verifyNPLY( this->components_.L2(), this->components_.NPL() );
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 458 of File 1 of Material {}", MAT );
    throw e;
  }

