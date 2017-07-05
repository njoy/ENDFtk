class Base {
public:

  double lowerEnergyLimit;
  double upperEnergyLimit;
  int NRO;
  int NAPS;

  Base( double EL, double EH, int nro, int naps )
    try:
      lowerEnergyLimit(EL),
      upperEnergyLimit(EH),
      NRO(nro),
      NAPS(naps)
  { 
    // Do a bit of input checking
    if( lowerEnergyLimit < 0.0 ){
      Log::error( "Encountered negative lower energy limit" );
      throw std::domain_error( "Lower energy limit (EL) must be positive" );
    }
    if( lowerEnergyLimit > upperEnergyLimit ){
      Log::error( "Lower energy limit is greater than upper energy limit." );
      throw std::domain_error( 
          "Lower energy limit must be less than upper energy limit" );
    }
    if( NRO == 0){
      if( ( NAPS != 0 ) and ( NAPS != 1) ){
        Log::error( "Encountered invalid NAPS value: {}.", NAPS );
        Log::info( "NAPS must be 0 or 1 when NRO=0" );
        throw std::domain_error( "Invalid NAPS value." );
      }
    }
    else if( NRO == 1 ){
      if( ( NAPS != 0 ) and ( NAPS != 1) and ( NAPS != 2 ) ){
        Log::error( "Encountered invalid NAPS value: {}.", NAPS );
        Log::info( "NAPS must be 0, 1 or 2 when NRO=1" );
        throw std::domain_error( "Invalid NAPS value." );
      }
    }
    else{
      Log::error( "Invalid NRO flag parameter: {}. ", NRO);
      Log::info( "Valid NRO values are 0 or 1" );
      throw std::domain_error("Invalid NRO value.");
    }
  }
  catch (std::exception& e ){
    Log::info( "Encountered trouble when creating Resolved::Base class" );
    throw e;
  }
};
