template< typename... Args >
Base( Args&&... args ) : CONT( std::forward<Args>(args)... ) { 
  if( this->EL() < 0.0 ){
    Log::error( "Encountered negative lower energy limit" );
    Log::info( "Lower energy limit value: {}", this->EL() );
    throw 0;
  }
  
  if( this->EH() < this->EL() ){
    Log::error( "Lower energy limit is greater than upper energy limit" );
    Log::info( "Lower energy limit value: {}", this->EL() );
    Log::info( "Upper energy limit value: {}", this->EH() );
    throw 1;
  }

  switch( this->LRU() ){
  case 0:
    if ( this->LRF() ){
      Log::error( "Encountered invalid LRF value: {}", this->LRF() );
      Log::info( "LRU value is zero");
      Log::info( "LRF must be zero when LRU is zero" );
      throw 3;
    }
    break;
  case 1:
    if ( ( ( this->LRF() < 1 )
           or ( this->LRF() > 4 ) )
         and ( this->LRF() != 7 ) ){
      Log::error( "Encountered invalid LRF value: {}", this->LRF() );
      Log::info( "LRU value is one");
      Log::info( "LRF must be 1, 2, 3, 4, or 7" );
      throw 3;
    }
    break;
  case 2:
    if ( ( this->LRF() < 1 ) or ( this->LRF() > 2 ) ){
      Log::error( "Encountered invalid LRF value: {}", this->LRF() );
      Log::info( "LRU value is two");
      Log::info( "LRF must be 1 or 2" );
      throw 3;
    }
    break;
  default:
    Log::error( "Encountered invalid LRU value: {}", this->LRU() );
    throw 2;
  }
  
  switch( this->NRO() ){
  case 0:
    if( ( this->NAPS() != 0 ) and ( this->NAPS() != 1) ){
      Log::error( "Encountered invalid NAPS value: {}.", this->NAPS() );
      Log::info( "NRO value is zero" );
      Log::info( "NAPS must be 0 or 1 when NRO is zero" );
      throw 5;
    }
    break;
    
  case 1:
    if( ( this->NAPS() < 0 ) or ( this->NAPS() > 2 ) ){
      Log::error( "Encountered invalid NAPS value: {}.", this->NAPS() );
      Log::info( "NRO value is one" );
      Log::info( "NAPS must be 0, 1 or 2 when NRO is one" );
      throw 5;
    }
    break;
    
  default:
    Log::error( "Invalid NRO value: {}. ", this->NRO() );
    Log::info( "Valid NRO values are 0 or 1" );
    throw 4;
  }
}

