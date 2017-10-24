template< typename Iterator >
static FissionEnergyReleaseData
readFissionEnergyReleaseData( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int LFC,
                              int NFC ) {
  switch ( LFC ) {
    case 0 : {
      // yes, this is ugly but NPLY is on the LIST
      Iterator temp = begin;
      ControlRecord cont( temp, end, lineNumber, MAT, 1, 458 );
      lineNumber--;
      if ( cont.L2() == 0 ) {
        return ThermalPoint( begin, end, lineNumber, MAT, 1, 458 );
      }
      else {
        return Polynomial( begin, end, lineNumber, MAT, 1, 458 );
      }
    }
    case 1 : return Tabulated( begin, end, lineNumber, MAT, 1, 458, NFC );
    default : {
      Log::error( "Encountered illegal LFC value" );
      Log::info( "LFC must be equal to 0 or 1" );
      Log::info( "LFC value: {}", LFC );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}

