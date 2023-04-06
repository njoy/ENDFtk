template< typename Iterator >
static Distribution
readDistribution( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT,
                  int LAW,
                  long lineLaw ) {
  switch ( LAW ) {
    case   1 : return ContinuumEnergyAngle(
                        begin, end, lineNumber, MAT, MF, MT );
    case   2 : return DiscreteTwoBodyScattering(
                        begin, end, lineNumber, MAT, MF, MT );
    case   8 : return EnergyTransfer( begin, end, lineNumber, MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LAW value" );
      Log::info( "LAW is equal to 1, 2 or 8" );
      Log::info( "LAW value: {}", LAW );
      Log::info( "Line number: {}", lineLaw - 1 );
      throw std::exception();
    }
  }
}
