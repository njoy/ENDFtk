template< typename Iterator >
DataType ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ), ldg_( head.L1() ) {
    switch ( this->ldg_ ) {
      case 0 : {
        independent_( begin, end, lineNumber, MAT, 1, head.MT() );
        break;
      }
      default : {
        Log::error( "Illegal value detected for the LDG flag (only 0 or 1 are allowed)" );
        throw std::exception();
      }
    }
    DataType< 451 >( head, begin, end, lineNumber, MAT );
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", head.MT(), MAT );
    throw e;
  }

