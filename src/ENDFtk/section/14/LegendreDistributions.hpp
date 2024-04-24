/**
 *  @class
 *  @brief Angular distributions as a function of incident energy using
 *         Legendre coefficients (LTT=1) for a given discrete photon
 *
 *  The LegendreDistributions class is used to represent the case in which
 *  the angular distributions in an MF14 section are given as Legendre
 *  coefficients.
 *
 *  See ENDF102, section 14.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreDistributions :
  protected AngularDistributions< LegendreCoefficients > {

public:

  /* constructor */
  #include "ENDFtk/section/14/LegendreDistributions/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const {

    return AngularDistributions< LegendreCoefficients >::C2(); }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const {

    return AngularDistributions< LegendreCoefficients >::C1();
  }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double photonEnergy() const { return this->EG(); }

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
