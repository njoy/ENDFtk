/**
 *  @brief Constructor
 *
 *  @param[in] lvalues   the l values and the resonance parameters
 */
UnresolvedBaseWithoutSpin(
  std::vector< LValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    lvalues_( std::move( lvalues ) ) {

      verifySize( this->NLS() );
    }
