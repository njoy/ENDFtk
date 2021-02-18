void checkBounds( unsigned int group, unsigned int order,
                  unsigned int dilution ) {

  // check group
  if ( group == 0 || group > this->num_groups_ ) {
    Log::error( "Group index {} is invalid with {} groups.",
                group, this->num_groups_ );
    throw;
  }

  checkBounds( order, dilution );
}

void checkBounds( unsigned int order, unsigned int dilution ) {

  // check order
  if ( order >= this->num_legendre_ ) {
    Log::error( "Legendre order {} is invalid with {} NL.",
                order, this->num_legendre_ );
    throw;
  }

  // check dilution
  if ( dilution >= this->num_dilutions_ ) {
    Log::error( "Dilution index {} is invalid with {} dilutions.",
                dilution, this->num_dilutions_ );
    throw;
  }
}
