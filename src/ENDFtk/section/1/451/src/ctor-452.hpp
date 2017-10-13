template< typename Iterator >
DataType ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ), lnu_( head.L2() ) {
    switch ( this->lnu_ ) {
      case 1 : {
        polynomial_( begin, end, lineNumber, MAT, 1, head.MT() );
        break;
      }
      case 2 : {
        tabulated_( begin, end, lineNumber, MAT, 1, head.MT() );
        break;
      }
      default : {
        Log::error( "Illegal value detected for the LNU flag (only 1 or 2 are allowed)" );
        throw std::exception();
      }
    }
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", head.MT(), MAT );
    throw e;
  }

