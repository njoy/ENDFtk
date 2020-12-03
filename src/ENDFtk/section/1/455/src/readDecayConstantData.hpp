template< typename Iterator >
static DecayConstantData
readDecayConstantData( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       int LDG ) {
  switch ( LDG ) {
    case 0 : return EnergyIndependentConstants( begin, end, lineNumber, MAT, MF, MT );
    case 1 : return EnergyDependent( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LDG value" );
      Log::info( "LDG must be equal to 0 or 1" );
      Log::info( "LDG value: {}", LDG );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}
