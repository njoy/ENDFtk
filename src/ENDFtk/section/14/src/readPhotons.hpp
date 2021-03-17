template< typename Iterator >
static std::vector< PhotonDistribution >
readPhotons( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT,
             long NI,
             long NK,
             long LTT) {

  std::vector< Component > sequence;
  sequence.reserve( NK );

  NK -= NI;
  while ( NI-- ) {

    sequence.push_back( IsotropicDiscretePhoton( begin, end, lineNumber,
                                                 MAT, MF, MT ) );
  }

  while ( NK-- ) {

    switch ( LTT ) {

      case 1 : sequence.push_back(
               LegendreDistributions( begin, end, lineNumber,
                                             MAT, MF, MT ) );
      case 2 : return TabulatedDistributions( begin, end, lineNumber, MAT, MF, MT );
      default : {
        Log::error( "Encountered illegal LTT value" );
        Log::info( "LTT must be equal to 1 or 2" );
        Log::info( "LTT value: {}", LTT );
        Log::info( "Line number: {}", lineNumber - 2 );
        throw std::exception();
      }
    }
  }

  return sequence;
}
