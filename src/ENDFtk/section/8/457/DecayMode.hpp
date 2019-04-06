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
  std::array< double, 2 > q_;
  std::array< double, 2 > branch_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DecayMode/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the decay chain
   */
  auto RTYP() const { return this->rtyp_; }

  /**
   *  @brief Return the decay chain
   */
  auto decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the final isomeric state
   */
  auto RFS() const { return this->rfs_; }

  /**
   *  @brief Return the final isomeric state
   */
  auto finalIsomericState() const { return this->RFS(); }

  /**
   *  @brief Return the Q value and its uncertainty
   */
  auto Q() const { return this->q_; }

  /**
   *  @brief Return the Q value and its uncertainty
   */
  auto qValue() const { return this->Q(); }

  /**
   *  @brief Return the branching ratio and its uncertainty
   */
  auto BR() const { return this->branch_; }

  /**
   *  @brief Return the branching ratio and its uncertainty
   */
  auto branchingRatio() const { return this->BR(); }
};
