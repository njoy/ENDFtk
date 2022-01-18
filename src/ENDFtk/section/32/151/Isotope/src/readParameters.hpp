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

  Iterator start = begin;
  long current = lineNumber;
  ControlRecord cont( start, end, lineNumber, MAT, MF, MT );
  int LCOMP = cont.L2();

  switch ( LCOMP ) {

    case 0: {

      switch ( LRU ) {

        // resolved resonances
        case 1 : {

          switch ( LRF ) {

            case 1 : return LimitedSingleLevelBreitWigner(
                                begin, end, lineNumber, MAT, MF, MT );
            case 2 : return LimitedMultiLevelBreitWigner(
                                begin, end, lineNumber, MAT, MF, MT );
            default : {

              Log::error( "Encountered illegal LRF value for LCOMP = 0" );
              Log::info( "LRF is equal to 1 or 2" );
              Log::info( "LRF value: {}", LRF );
              Log::info( "Line number: {}", lineNumber );
              throw std::exception();
            }
          }
        }
        default : {

          Log::error( "Encountered illegal LRU value" );
          Log::info( "LRU is should be 1 (resolved) for LCOMP = 0" );
          Log::info( "LRU value: {}", LRU );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception();
        }
      }
    }
    default : {

      Log::error( "Encountered illegal LCOMP value" );
      Log::info( "LCOMP is either 0 (limited), 1 (general) or 2 (compact)" );
      Log::info( "LCOMP value: {}", LCOMP );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
  switch ( LRU ) {

    // special case: only scattering radius is given
    case 0 : return SpecialCase( begin, end, lineNumber, MAT, MF, MT );
    // resolved resonances
    case 1 : {

      switch ( LRF ) {

        case 1 : return SingleLevelBreitWigner(
                            begin, end, lineNumber, MAT, MF, MT );
        case 2 : return MultiLevelBreitWigner(
                            begin, end, lineNumber, MAT, MF, MT );
        case 3 : return ReichMoore(
                            begin, end, lineNumber, MAT, MF, MT );
        case 7 : return RMatrixLimited(
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

            case 0 : return UnresolvedEnergyIndependent(
                                begin, end, lineNumber, MAT, MF, MT );
            case 1 : return UnresolvedEnergyDependentFissionWidths(
                                begin, end, lineNumber, MAT, MF, MT );
            default : {

              Log::error( "Encountered illegal LFW value" );
              Log::info( "LFW is equal to 0 or 1" );
              Log::info( "LFW value: {}", LFW );
              throw std::exception();
            }
          }
        }
        case 2 : return UnresolvedEnergyDependent(
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
