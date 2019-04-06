/** 
 *  @brief Constructor
 *
 *  @param[in] rtyp       the decay chain
 *  @param[in] rfs        the final isomeric state
 *  @param[in] q          the Q value
 *  @param[in] dq         the uncertainty on the Q value
 *  @param[in] br         the branching ratio value
 *  @param[in] dbr        the uncertainty on the branching ratio value
 */
DecayMode( double rtyp, double rfs,
           double q, double dq,
           double br, double dbr ) :
  rtyp_( rtyp ), rfs_( rfs ), q_( {{q, dq}} ), branch_( {{br, dbr}} ) {}
