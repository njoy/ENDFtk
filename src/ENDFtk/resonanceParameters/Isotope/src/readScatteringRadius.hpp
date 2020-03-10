template< typename Iterator >
static std::optional< ScatteringRadius >
readScatteringRadius( Iterator& begin,
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
    case 1 : return ScatteringRadius( begin, end, lineNumber, MAT, MF, MT );
    default : {

      Log::error( "Encountered illegal NRO value" );
      Log::info( "NRO is either 0 (no energy dependent scattering radius "
                 "given) or 2 (an energy dependent scattering radius is "
                 "given)" );
      Log::info( "NRO value: {}", NRO );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception();
    }
  }
}
