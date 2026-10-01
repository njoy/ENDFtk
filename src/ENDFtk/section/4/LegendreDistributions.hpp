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

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] distributions   the sequence of angular distributions
   */
  LegendreDistributions( std::vector< long >&& boundaries,
                         std::vector< long >&& interpolants,
                         std::vector< LegendreCoefficients >&& distributions ) :
    AngularDistributions( std::move( interpolants ), std::move( boundaries ),
                          std::move( distributions ) ) {}

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
