/**
 *  @brief Ensure requested indices are valid.
 *
 *  @param[in] group    the group index
 *  @param[in] order    the Legendre order
 *  @param[in] dilution the dilution index
 */
void checkBounds( unsigned int group, unsigned int order,
                  unsigned int dilution ) const {

  // check group
  if ( group == 0 || group > this->num_groups_ ) {
    Log::error( "Group index {} is invalid with {} groups.",
                group, this->num_groups_ );
    throw std::exception();
  }

  checkBounds( order, dilution );
}

/**
 *  @brief Ensure requested indices are valid.
 *
 *  @param[in] order    the Legendre order
 *  @param[in] dilution the dilution index
 */
void checkBounds( unsigned int order, unsigned int dilution ) const {

  // check order
  if ( order >= this->num_legendre_ ) {
    Log::error( "Legendre order {} is invalid with {} NL.",
               order, this->num_legendre_ );
    throw std::exception();
  }

  // check dilution
  if ( dilution >= this->num_dilutions_ ) {
    Log::error( "Dilution index {} is invalid with {} dilutions.",
                dilution, this->num_dilutions_ );
    throw std::exception();
  }
}
