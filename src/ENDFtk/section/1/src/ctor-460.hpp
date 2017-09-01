template< typename Iterator >
DataType ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ) {
    long LO = head.L1();
    switch ( LO ) {
      case 1 : {
        discrete_( readRecords( begin, end, lineNumber, MAT,
                   head.N1(), 1 ,
                   "Number of discrete photon records (NG) must be greater than zero" ) );
        break;
      }
      case 2 : {
        continuous_( begin, end, lineNumber, MAT, 1, 460 );
        break;
      }
      default : {
        Log::error( "Illegal value detected for the LO flag (only 1 or 2 are allowed)" );
        throw std::exception();
      }
    }
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", 460, MAT );
    throw e;
  }

