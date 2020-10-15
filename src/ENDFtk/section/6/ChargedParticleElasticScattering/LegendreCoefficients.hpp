/**
 *  @class
 *  @brief Charged particle elastic scattering given as Legendre coeffcients
 *
 *  See ENDF102, section 6.2.6 for more information.
 */
class LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the representation type
   */
  static constexpr int LTP() { return 2; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LTP(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order or number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the Legendre coefficients
   */
  auto C() const { return ListRecord::list(); }

  /**
   *  @brief Return the Legendre coefficients
   */
  auto coefficients() const { return this->C(); }

  using ListRecord::NC;
  using ListRecord::print;
};
