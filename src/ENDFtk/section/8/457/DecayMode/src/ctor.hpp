/**
 *  @brief Constructor
 *
 *  @param[in] chain     the decay chain
 *  @param[in] state     the final isomeric state
 *  @param[in] q         the Q value
 *  @param[in] dq        the uncertainty on the Q value
 *  @param[in] ratio     the branching ratio value
 *  @param[in] dratio    the uncertainty on the branching ratio value
 */
DecayMode( double chain, double state,
           double q, double dq,
           double ratio, double dratio ) :
  rtyp_( chain ), rfs_( state ), q_( {{q, dq}} ),
  branch_( {{ratio, dratio}} ) {}
