template< typename Iterator >
std::variant< ListRecord, TabulationRecord >
readData( Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT,
          int LNU ) {
  switch ( LNU ) {
    case 1 : return ListRecord( begin, end, lineNumber, MAT, 1, 452 );
    case 2 : return TabulationRecord( begin, end, lineNumber, MAT, 1, 452 );
    default : {
      Log::error( "Illegal value detected for the LNU flag (only 1 or 2 are allowed)" );
      throw std::exception();
    }
  }
}

