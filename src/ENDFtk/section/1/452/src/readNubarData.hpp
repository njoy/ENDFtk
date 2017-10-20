template< typename Iterator >
nubar::NubarData
readData( Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT,
          int MT,
          int LNU ) {
  switch ( LNU ) {
    case 1 : return nubar::Polynomial( begin, end, lineNumber, MAT, 1, MT );
    case 2 : return nubar::Tabulated( begin, end, lineNumber, MAT, 1, MT );
    default : {
      Log::error( "Illegal value detected for the LNU flag (only 1 or 2 are allowed)" );
      throw std::exception();
    }
  }
}

