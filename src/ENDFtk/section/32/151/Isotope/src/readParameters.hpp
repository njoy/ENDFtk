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
    case 1: {

      switch ( LRU ) {

        // resolved resonances
        case 1 : {

          switch ( LRF ) {

            case 1 : return GeneralSingleLevelBreitWigner(
                                begin, end, lineNumber, MAT, MF, MT );
            case 2 : return GeneralMultiLevelBreitWigner(
                                begin, end, lineNumber, MAT, MF, MT );
            case 3 : return GeneralReichMoore(
                                begin, end, lineNumber, MAT, MF, MT );
            case 7 : return GeneralRMatrixLimited(
                                begin, end, lineNumber, MAT, MF, MT );
            default : {

              Log::error( "Encountered illegal LRF value for LCOMP = 1" );
              if ( LRF != 4 ) {

                Log::info( "LRF is equal to 1, 2, 3, 4 or 7" );
                Log::info( "LRF value: {}", LRF );
              }
              else {

                Log::info( "LRF equal to 4 (Adler-Adler) is currently unsupported" );
              }
              Log::info( "Line number: {}", lineNumber );
              throw std::exception();
            }
          }
        }
        default : {

          Log::error( "Encountered illegal LRU value" );
          Log::info( "LRU is should be 1 (resolved) for LCOMP = 1" );
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
}
