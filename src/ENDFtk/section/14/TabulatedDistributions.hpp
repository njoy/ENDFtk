/**
 *  @class
 *  @brief Angular distributions as a function of incident energy using
 *         tabulated functions (LTT=2) for a given discrete photon
 *
 *  The LegendreDistributions class is used to represent the case in which
 *  the angular distributions in an MF4 section are given as tabulated
 *  functions.
 *
 *  See ENDF102, section 14.2.3 for more information.
 */
class TabulatedDistributions :
  protected AngularDistributions< TabulatedDistribution > {

public:

  /* constructor */
  #include "ENDFtk/section/14/TabulatedDistributions/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const {

    return AngularDistributions< TabulatedDistribution >::C2(); }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const {

    return AngularDistributions< TabulatedDistribution >::C1();
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
  static constexpr int LTT() { return 2; }

  /**
   *  @brief Return the distribution law
   */
  int LAW() const { return this->LTT(); }

  using AngularDistributions< TabulatedDistribution >::NR;
  using AngularDistributions< TabulatedDistribution >::NE;
  using AngularDistributions< TabulatedDistribution >::interpolants;
  using AngularDistributions< TabulatedDistribution >::boundaries;
  using AngularDistributions< TabulatedDistribution >::incidentEnergies;
  using AngularDistributions< TabulatedDistribution >::angularDistributions;

  using AngularDistributions< TabulatedDistribution >::NC;
  using AngularDistributions< TabulatedDistribution >::print;
};
