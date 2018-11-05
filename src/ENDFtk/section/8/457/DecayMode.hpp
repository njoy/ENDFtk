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
class DecayMode {

  /* members */
  double rtyp_;
  double rfs_;
  std::tuple< double, double > q_;
  std::tuple< double, double > branch_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DecayMode/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the decay chain
   */
  auto decayChain() const { return this->rtyp_; }

  /**
   *  @brief Return the final isomeric state
   */
  auto finalIsomericState() const { return this->rfs_; }

  /**
   *  @brief Return the decay chain
   */
  auto qValue() const { return this->q_; }

  /**
   *  @brief Return the decay chain
   */
  auto branchingRatio() const { return this->branch_; }
};
