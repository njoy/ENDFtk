/**
 *  @class
 *  @brief A single ENDF decay mode
 *
 *  The DecayMode class is used to store the decay chain RTYP, the final
 *  isomeric state RFS, the Q value and its uncertainty and the branching
 *  ratio and its uncertainty for a decay mode from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecayMode {

  /* members */

  double rtyp_;
  double rfs_;
  std::array< double, 2 > q_;
  std::array< double, 2 > branch_;

  /* auxiliary functions */

public:

  /* constructor */

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

  /* get methods */

  /**
   *  @brief Return the decay chain
   */
  double RTYP() const { return this->rtyp_; }

  /**
   *  @brief Return the decay chain
   */
  double decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the final isomeric state
   */
  double RFS() const { return this->rfs_; }

  /**
   *  @brief Return the final isomeric state
   */
  double finalIsomericState() const { return this->RFS(); }

  /**
   *  @brief Return the Q value and its uncertainty
   */
  auto Q() const {

    using namespace njoy::tools;
    return std20::views::all( this->q_ );
  }

  /**
   *  @brief Return the Q value and its uncertainty
   */
  auto qValue() const { return this->Q(); }

  /**
   *  @brief Return the branching ratio and its uncertainty
   */
  auto BR() const {

    using namespace njoy::tools;
    return std20::views::all( this->branch_ );
  }

  /**
   *  @brief Return the branching ratio and its uncertainty
   */
  auto branchingRatio() const { return this->BR(); }
};
