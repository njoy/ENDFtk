void validate(){
  if ( ( this->LAD() != 0 ) and ( this->LAD() != 1 ) ){
    Log::error( "Encountered illegal LAD value" );
    Log::info( "LAD value is required to be zero or one" );
    Log::info( "LAD value: {}", this->LAD() );
    throw std::exception();
  }
  if ( this->NLSC() < this->NLS() ){
    Log::error( "Encountered illegal NLSC value" );
    Log::info( "NLSC is required to be greater than or equal to NLS" );
    Log::info( "NLS value: {}", this->NLS() );
    Log::info( "NLSC value: {}", this->NLSC() );
    throw std::exception();
  }
}
