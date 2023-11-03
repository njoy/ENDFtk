template< typename Iterator >
static std::optional< ScatteringRadiusCovariances >
readScatteringRadiusCovariances( Iterator& begin,
                                 const Iterator& end,
                                 long& lineNumber,
                                 int MAT,
                                 int MF,
                                 int MT,
                                 int NRO ) {

  switch ( NRO ) {

    // no energy dependent scattering radius
    case 0 : return std::nullopt;
    // energy dependent scattering radius
    case 1 : return ScatteringRadiusCovariances( begin, end, lineNumber,
                                                 MAT, MF, MT );
    default : {

      Log::error( "Encountered illegal NRO value" );
      Log::info( "NRO is either 0 (no energy dependent scattering radius "
                 "given) or 1 (energy dependent scattering radius covariances "
                 "are given)" );
      Log::info( "NRO value: {}", NRO );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
}
