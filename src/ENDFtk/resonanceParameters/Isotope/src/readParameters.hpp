template< typename Iterator >
static ResonanceRange::ResonanceParameters
readParameters( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT,
                int LRU,
                int LRF,
                int LFW ) {

  switch ( LRU ) {

    // special case: only scattering radius is given
    case 0 : return SpecialCase( begin, end, lineNumber, MAT, MF, MT );
    // resolved resonances
    case 1 : {

      switch ( LRF ) {

        case 1 : return resolved::SingleLevelBreitWigner(
                            begin, end, lineNumber, MAT, MF, MT );
        case 2 : return resolved::MultiLevelBreitWigner(
                            begin, end, lineNumber, MAT, MF, MT );
        case 3 : return resolved::ReichMoore(
                            begin, end, lineNumber, MAT, MF, MT );
        case 7 : return resolved::RMatrixLimited(
                            begin, end, lineNumber, MAT, MF, MT );
        default : {

          Log::error( "Encountered illegal LRF value" );
          Log::info( "LRF is equal to 1, 2, 3, 4 or 7" );
          Log::info( "LRF value: {}", LRF );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception();
        }
      }
    }
    // unresolved resonances
    case 2 : {

      switch ( LRF ) {

        case 1 : {

          switch ( LFW ) {

            case 0 : return unresolved::EnergyIndependent(
                                begin, end, lineNumber, MAT, MF, MT );
            case 1 : return unresolved::EnergyDependentFissionWidths(
                                begin, end, lineNumber, MAT, MF, MT );
            default : {

              Log::error( "Encountered illegal LFW value" );
              Log::info( "LFW is equal to 0 or 1" );
              Log::info( "LFW value: {}", LFW );
              throw std::exception();
            }
          }
        }
        case 2 : return unresolved::EnergyDependent(
                            begin, end, lineNumber, MAT, MF, MT );
        default : {

          Log::error( "Encountered illegal LRF value" );
          Log::info( "LRF is equal to 1 or 2" );
          Log::info( "LRF value: {}", LRF );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception();
        }
      }
    }
    default : {

      Log::error( "Encountered illegal LRU value" );
      Log::info( "LRU is either 1 (resolved) or 2 (unresolved)" );
      Log::info( "LRU value: {}", LRU );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
}
