/**
 *  @class
 *  @brief Angular distributions as a function of incident energy using
 *         Legendre coefficients (LTT=1)
 *
 *  The LegendreDistributions class is used to represent the case in which
 *  the angular distributions in an MF4 section are given as Legendre
 *  coefficients.
 *
 *  See ENDF102, section 4.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreDistributions :
  protected AngularDistributions< LegendreCoefficients > {

public:

  /* constructor */
  #include "ENDFtk/section/4/LegendreDistributions/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return false; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicDistributions() const { return this->LI(); }

  /**
   *  @brief Return the distribution law
   */
  static constexpr int LTT() { return 1; }

  /**
   *  @brief Return the distribution law
   */
  int LAW() const { return this->LTT(); }

  using AngularDistributions< LegendreCoefficients >::NR;
  using AngularDistributions< LegendreCoefficients >::numberInterpolationRegions;
  using AngularDistributions< LegendreCoefficients >::NE;
  using AngularDistributions< LegendreCoefficients >::numberIncidentEnergies;
  using AngularDistributions< LegendreCoefficients >::INT;
  using AngularDistributions< LegendreCoefficients >::interpolants;
  using AngularDistributions< LegendreCoefficients >::NBT;
  using AngularDistributions< LegendreCoefficients >::boundaries;
  using AngularDistributions< LegendreCoefficients >::incidentEnergies;
  using AngularDistributions< LegendreCoefficients >::angularDistributions;

  using AngularDistributions< LegendreCoefficients >::NC;
  using AngularDistributions< LegendreCoefficients >::print;
};
