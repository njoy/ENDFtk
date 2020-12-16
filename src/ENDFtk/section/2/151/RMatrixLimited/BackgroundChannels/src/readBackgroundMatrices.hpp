template< typename Iterator >
static std::vector< std::optional< BackgroundRMatrix > >
readBackgroundMatrices( Iterator& begin, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT,
                        int NCH, int KBK ) {

  std::vector< std::optional< BackgroundRMatrix > >
  background( NCH, std::nullopt );

  if ( ( KBK < 0 ) || ( KBK > NCH ) ) {

    Log::error( "Encountered illegal KBK value" );
    Log::info( "KBK must be between zero and NCH" );
    Log::info( "NCH value: {}", NCH );
    Log::info( "KBK value: {}", KBK );
    throw std::exception();
  }

  while( KBK-- ) {

    Iterator temp = begin;
    long line = lineNumber;
    ControlRecord cont( temp, end, line, MAT, MF, MT );
    int LCH = cont.L1();
    int LBK = cont.L2();

    if ( ( LCH <= 0 ) || ( LCH > NCH ) ) {

      Log::error( "Encountered illegal LCH value" );
      Log::info( "LCH must be between 1 and NCH" );
      Log::info( "NCH value: {}", NCH );
      Log::info( "LCH value: {}", LCH );
      throw std::exception();
    }

    switch ( LBK ) {

      case 0 : {

        background[ LCH - 1 ] =
            NoBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
        break;
      }
      case 1 : {

        background[ LCH - 1 ] =
            TabulatedBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
        break;
      }
      case 2 : {

        background[ LCH - 1 ] =
            SammyBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
        break;
      }
      case 3 : {

        background[ LCH - 1 ] =
            FrohnerBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
        break;
      }
      default : {

        Log::error( "Encountered illegal LBK value" );
        Log::info( "LBK must be between 0 and 3" );
        Log::info( "LBK value: {}", LBK );
        throw std::exception();
      }
    }
  }
  return background;
}
