/**
 *  @class
 *  @brief R-matrix limited resonance parameters
 *
 *  The RMatrixLimited class is used to represent the R-matrix limited resonance
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class RMatrixLimited : protected Base {

public:

  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup.hpp"

private:

  /* fields */
  int ifg_;
  int krm_;
  int krl_;

  std::vector< SpinGroup > spin_groups_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() const { return 1; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() const { return RMatrixLimited::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() const { return 7; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() const { return RMatrixLimited::LRF(); }

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
   *  @brief Return the spin groups
   */
  auto spinGroups() const { return ranges::view::all( this->spin_groups_ ); }

  using Base::EL;
  using Base::lowerEnergy;
  using Base::EH;
  using Base::upperEnergy;
  using Base::NRO;
  using Base::energyDependentScatteringRadius;
  using Base::NAPS;
  using Base::scatteringRadiusCalculationOption;
};
