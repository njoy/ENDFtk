/**
 *  @class
 *  @brief Angular distributions as a function of incident energy using
 *         tabulated functions (LTT=2)
 *
 *  The LegendreDistributions class is used to represent the case in which
 *  the angular distributions in an MF4 section are given as tabulated
 *  functions.
 *
 *  See ENDF102, section 4.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedDistributions :
  protected AngularDistributions< TabulatedDistribution > {

public:

  /* constructor */
  #include "ENDFtk/section/4/TabulatedDistributions/src/ctor.hpp"

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
  static constexpr int LTT() { return 2; }

  /**
   *  @brief Return the distribution law
   */
  int LAW() const { return this->LTT(); }

  using AngularDistributions< TabulatedDistribution >::NR;
  using AngularDistributions< TabulatedDistribution >::numberInterpolationRegions;
  using AngularDistributions< TabulatedDistribution >::NE;
  using AngularDistributions< TabulatedDistribution >::numberIncidentEnergies;
  using AngularDistributions< TabulatedDistribution >::INT;
  using AngularDistributions< TabulatedDistribution >::interpolants;
  using AngularDistributions< TabulatedDistribution >::NBT;
  using AngularDistributions< TabulatedDistribution >::boundaries;
  using AngularDistributions< TabulatedDistribution >::incidentEnergies;
  using AngularDistributions< TabulatedDistribution >::angularDistributions;

  using AngularDistributions< TabulatedDistribution >::NC;
  using AngularDistributions< TabulatedDistribution >::print;
};
