template< typename Iterator >
static nubar::DecayConstantData
readDecayConstantData( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       int LDG ) {
  switch ( LDG ) {
    case 0 : return nubar::Constant( begin, end, lineNumber, MAT, MF, MT );
    case 1 : return nubar::EnergyDependent( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Illegal value detected for the LDG flag (only 0 or 1 are allowed)" );
      throw std::exception();
    }
  }
}

