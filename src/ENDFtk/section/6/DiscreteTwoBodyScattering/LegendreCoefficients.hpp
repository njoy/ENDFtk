/**
 *  @class
 *  @brief An angular distribution given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this is ListRecord based).
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifyLANG.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the LANG value
   */
  static constexpr int LANG() { return 0; }

  /**
   *  @brief Return the number of values (equal to the Legendre order)
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int legendreOrder() const { return this->NL(); }

  /**
   *  @brief Return the Legendre coefficients in the distribution (a0 is not
   *         present and assumed to be equal to 1)
   */
  auto A() const { return ListRecord::list(); }

  /**
   *  @brief Return the Legendre coefficients in the distribution (a0 is not
   *         present and assumed to be equal to 1)
   */
  auto coefficients() const { return this->A(); }

  using ListRecord::NC;
  using ListRecord::print;
};
