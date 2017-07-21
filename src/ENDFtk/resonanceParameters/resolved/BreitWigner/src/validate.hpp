void validate(){
  Base{ this->EL(), this->EH(), 1, 1, this->NRO(), this->NAPS() };
  if ( not this->NLS() ){
    Log::error( "NLS required to be positive" );
    Log::error( "NLS value: {}", this->NLS() );
    throw std::exception();
  }
}
