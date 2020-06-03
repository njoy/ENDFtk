/*
 * @brief Return matrix element from transfer matrix.
 * @param in_group  Incoming energy group (GENDF ordering)
 * @param out_group Outgoing energy group (GENDF ordering)
 * @param order     Legendre order
 * @param idil      Index of dilution (0-based)
 */
double getMatrixElement( int in_group,
                         int out_group,
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
  else if( in_group <= 0 or in_group > num_groups_ ) {
    Log::info( "In-group {} is invalid with {} groups",
               in_group, num_groups_ );
    throw std::exception();
  }
  else if( out_group <= 0 or out_group > num_groups_ ) {
    Log::info( "Out-group {} is invalid with {} groups",
               out_group, num_groups_ );
    throw std::exception();
  }

  // in_group not in dataset
  if( data_.count( in_group ) == 0 )
    return 0.0;

  // retrieve stored data
  auto record = data_.at(in_group);
  auto data = record.values();
  int lowest = record.lowestGroup();
  int npos = record.numSecondaryPositions() - 1;

  // find index
  int idx = out_group - lowest;

  // out_group not in dataset
  if( idx >= npos or idx < 0 )
    return 0.0;

  // return value from dataset
  return data[ numLegendre()*numSigma0()*idx + numLegendre()*idil + order ];

}


/*
 * @brief Return matrix element from transfer matrix.
          Assume l=0, idil=0.
 * @param in_group  Incoming energy group (GENDF ordering)
 * @param out_group Outgoing energy group (GENDF ordering)
 */
double getMatrixElement( int in_group, int out_group ) {
  return getMatrixElement( in_group, out_group, 0, 0 );
}
