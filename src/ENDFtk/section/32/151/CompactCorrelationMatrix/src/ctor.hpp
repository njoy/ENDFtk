/**
 *  @brief Constructor
 *
 *  @param[in] order          the order of the (square) correlation matrix
 *  @param[in] i              the i coordinates
 *  @param[in] j              the j coordinates
 *  @param[in] correlations   the correlation values
 *  @param[in] ndigits        the number of digits for compacting (default = 6)
 */
CompactCorrelationMatrix( unsigned int order,
                          std::vector< unsigned int >&& i,
                          std::vector< unsigned int >&& j,
                          std::vector< double >&& correlations,
                          unsigned int ndigits = 6 )
  try : nnn_( order ), i_( std::move( i ) ), j_( std::move( j ) ),
        correlations_( std::move( correlations ) ),
        ndigits_( ndigits ) {

    verifySize( this->i_.size(), this->j_.size(), this->correlations_.size() );
    verifyDigits( this->ndigits_ );
  }
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a compact correlation "
               "matrix" );
    throw;
  }
