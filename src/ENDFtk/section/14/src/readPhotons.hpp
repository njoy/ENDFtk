template< typename Iterator >
static std::vector< PhotonDistribution >
readPhotons( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT,
             long LI,
             long NI,
             long NK,
             long LTT) {

  std::vector< PhotonDistribution > sequence;
  if ( LI != 1 ) {

    sequence.reserve( NK );

    // NK is the total number of photon subsections
    // subtract the NI discrete photons we'll read first
    NK -= NI;

    while ( NI-- ) {

      sequence.push_back( IsotropicDiscretePhoton( begin, end, lineNumber,
                                                   MAT, MF, MT ) );
    }

    while ( NK-- ) {

      switch ( LTT ) {

        case 1 : {

          sequence.push_back( LegendreDistributions( begin, end, lineNumber,
                                                     MAT, MF, MT ) );
          break;
        }
        case 2 : {

          sequence.push_back( TabulatedDistributions( begin, end, lineNumber,
                                                      MAT, MF, MT ) );
          break;
        }
        default : {
          Log::error( "Encountered illegal LTT value" );
          Log::info( "LTT must be equal to 1 or 2" );
          Log::info( "LTT value: {}", LTT );
          Log::info( "Line number: {}", lineNumber - 2 );
          throw std::exception();
        }
      }
    }
  }

  return sequence;
}
