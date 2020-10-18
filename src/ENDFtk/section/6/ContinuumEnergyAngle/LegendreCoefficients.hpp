/**
 *  @class
 *  @brief Angular distributions are given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this gives coefficients for each outgoing energy value as
 *  well).
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class LegendreCoefficients : protected Base {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the representation type
   */
  static constexpr int LANG() { return 1; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LANG(); }

  using Base::E;
  using Base::incidentEnergy;
  using Base::ND;
  using Base::numberDiscreteEnergies;
  using Base::NA;
  using Base::numberAngularParameters;
  using Base::NW;
  using Base::NEP;
  using Base::numberSecondaryEnergies;
  using Base::EP;
  using Base::energies;
  using Base::F0;
  using Base::totalEmissionProbabilities;

  /**
   *  @brief Return the Legendre order
   */
  long NL() const { return Base::NA(); }

  /**
   *  @brief Return the Legendre order
   */
  long legendreOrder() const { return this->NL(); }

  /**
   *  @brief Return the Legendre coefficients (one set for each outgoing energy)
   */
  auto A() const { return Base::data(); }

  /**
   *  @brief Return the Legendre coefficients (one set for each outgoing energy)
   */
  auto coefficients() const { return this->A(); }

  using Base::NC;
  using Base::print;
};
