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
class ENDFTK_PYTHON_EXPORT TabulatedDistributions :
  protected AngularDistributions< TabulatedDistribution > {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedDistributions() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the photon energy
   *  @param[in] level           the energy of the level from which the photon
   *                             originates
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] distributions   the sequence of angular distributions
   */
  TabulatedDistributions( double energy, double level,
                          std::vector< long >&& boundaries,
                          std::vector< long >&& interpolants,
                          std::vector< TabulatedDistribution >&& distributions ) :
    AngularDistributions( std::move( interpolants ), std::move( boundaries ),
                          std::move( distributions ), energy, level ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  TabulatedDistributions( Iterator& begin,
                          const Iterator& end,
                          long& lineNumber,
                          int MAT,
                          int MF,
                          int MT ) :
    AngularDistributions( begin, end, lineNumber, MAT, MF, MT  ) {}

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
