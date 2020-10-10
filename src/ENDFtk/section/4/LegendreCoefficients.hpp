/**
 *  @class
 *  @brief An angular distribution given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  See ENDF102, section 4.2.1 for more information.
 */
class LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */

public:
  /* constructor */
  #include "ENDFtk/section/4/LegendreCoefficients/src/ctor.hpp"

  /* get methods */

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
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int NL() const { return ListRecord::NPL(); }

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
