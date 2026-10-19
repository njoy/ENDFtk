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

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  LegendreDistributions() = default;
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
  LegendreDistributions( double energy, double level,
                         std::vector< long >&& boundaries,
                         std::vector< long >&& interpolants,
                         std::vector< LegendreCoefficients >&& distributions ) :
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
  LegendreDistributions( Iterator& begin,
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
