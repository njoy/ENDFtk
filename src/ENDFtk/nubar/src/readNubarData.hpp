template< typename Iterator >
static nubar::NubarData
readNubarData( Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT,
               int MF,
               int MT,
               int LNU ) {
  switch ( LNU ) {
    case 1 : return nubar::Polynomial( begin, end, lineNumber, MAT, MF, MT );
    case 2 : return nubar::Tabulated( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LNU value" );
      Log::info( "LNU must be equal to 1 or 2" );
      Log::info( "LNU value: {}", LNU );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}

