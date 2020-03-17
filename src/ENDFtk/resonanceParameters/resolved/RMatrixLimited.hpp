/**
 *  @class
 *  @brief R-matrix limited resonance parameters
 *
 *  The RMatrixLimited class is used to represent the R-matrix limited resonance
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class RMatrixLimited {

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/verifySize.hpp"

public:

  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ParticlePairs.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ResonanceChannels.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ResonanceParameters.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup.hpp"

private:

  /* fields */
  bool ifg_;
  bool krl_;
  int krm_;

  ParticlePairs particle_pairs_;
  std::vector< SpinGroup > spin_groups_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/readSpinGroups.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 1; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return RMatrixLimited::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 7; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return RMatrixLimited::LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr int averageFissionWidthFlag() const {

    return RMatrixLimited::LFW();
  }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool IFG() const { return this->ifg_; }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool reducedWidths() const { return this->IFG(); }

  /**
   *  @brief Return the resonance formalism to be employed
   */
  auto KRM() const { return this->krm_; }

  /**
   *  @brief Return the resonance formalism to be employed
   */
  auto formalism() const { return this->KRM(); }

  /**
   *  @brief Return the non relativistic kinematics flag
   */
  bool KRL() const { return this->krl_; }

  /**
   *  @brief Return the non relativistic kinematics flag
   */
  bool nonRelativisticKinematics() const { return this->KRL(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJS() const { return this->spin_groups_.size(); }

  /**
   *  @brief Return the number of spin groups
   */
  auto numberSpinGroups() const { return this->NJS(); }

  /**
   *  @brief Return the particle pair information
   */
  const auto& particlePairs() const { return this->particle_pairs_; }

  /**
   *  @brief Return the spin groups
   */
  auto spinGroups() const { return ranges::view::all( this->spin_groups_ ); }

  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/print.hpp"
};
