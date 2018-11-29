template< typename Iterator >
static SubSection
readSubSection( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT ) {

  PartialProbability probability( begin, end, lineNumber,
                                  MAT, MF, MT );
  switch ( probability.LF() ) {
    case 1 : return SubSection(
                        std::move( probability ),
                        TabulatedSpectrum( begin, end, lineNumber,
                                           MAT, MF, MT ) );
    case 5 : return SubSection(
                        std::move( probability ),
                        GeneralEvaporationSpectrum( begin, end, lineNumber,
                                                    MAT, MF, MT ) );
    case 7 : return SubSection(
                        std::move( probability ),
                        MaxwellianFissionSpectrum( begin, end, lineNumber,
                                                   MAT, MF, MT ) );
    case 9 : return SubSection(
                        std::move( probability ),
                        EvaporationSpectrum( begin, end, lineNumber,
                                             MAT, MF, MT ) );
    case 11 : return SubSection(
                         std::move( probability ),
                         WattSpectrum( begin, end, lineNumber,
                                       MAT, MF, MT ) );
    case 12 : return SubSection(
                         std::move( probability ),
                         MadlandNixSpectrum( begin, end, lineNumber,
                                             MAT, MF, MT ) );
    default : {
      Log::error( "Encountered illegal LF value" );
      Log::info( "LF must be equal to 1, 5, 7, 9, 11 or 12" );
      Log::info( "LF value: {}", probability.LF() );
      Log::info( "Line number: {}", lineNumber - probability.NC() );
      throw std::exception();
    }
  }
}
