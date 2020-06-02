double getCrossSection( int group,
                        int order,
                        int idil ) {

  // error checking
  if( order > legendreOrder() ) {
    Log::info( "{} is greater than Legendre order of dataset ({})",
               order, legendreOrder() );
    throw std::exception();
  }
  else if( idil >= num_sigma0_ ) {
    Log::info( "Index {} exceeds number of dilutions in dataset ({})",
               idil, num_sigma0_ );
    throw std::exception();
  }
  else if( group <= 0 or group > num_groups_ ) {
    Log::info( "Group {} is invalid with {} groups",
               group, num_groups_ );
    throw std::exception();
  }

  // group not in dataset
  if( data_.count( group ) == 0 )
    return 0.0;

  // select dilution and legendre order from dataset
  auto data = data_.at(group).values();
  return data[numLegendre()*idil + order];

}

double getCrossSection( int group ) {
  return getCrossSection( group, 0, 0 );
}
