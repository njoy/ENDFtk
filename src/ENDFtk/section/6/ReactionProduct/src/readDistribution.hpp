template< typename Iterator >
static Distribution
readDistribution( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MT,
                  int LAW ) {
  switch ( LAW ) {
    case  -4 :
    case  -5 :
    case -14 :
    case -15 : {
      if ( MT != 18 ) {
        Log::error( "Encountered illegal LAW value for non fission reaction" );
        Log::info( "LAW can only be negative for MT=18" );
        Log::info( "MT value: {}", MT );
        Log::info( "Line number: {}", lineNumber - 1 );
        throw std::exception();
      }
      return DefinedElsewhere( LAW );
    }
    case   0 : return Unknown();
    case   1 : return ContinuumEnergyAngle( begin, end, lineNumber, MAT, 6, MT );
    case   2 : return DiscreteTwoBodyScattering( begin, end, lineNumber, MAT, 6, MT );
    case   3 : return IsotropicDiscreteEmission();
    case   4 : return DiscreteTwoBodyRecoils();
    case   5 : return ChargedParticleElasticScattering( begin, end, lineNumber, MAT, 6, MT );
    case   6 : return NBodyPhaseSpace( begin, end, lineNumber, MAT, 6, MT );
    case   7 : return LaboratoryAngleEnergy( begin, end, lineNumber, MAT, 6, MT );
    default : {
      Log::error( "Encountered illegal LAW value" );
      Log::info( "LAW must be negative or equal to a value between 0 and 7" );
      Log::info( "LAW value: {}", LAW );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}
