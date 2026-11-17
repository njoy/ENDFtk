/**
 *  @class
 *  @brief Reich-Moore resonance parameters
 *
 *  The SingleLevelBreitWigner class is used to represent the Reich-Moore
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReichMoore :
  protected BreitWignerReichMooreBase< ReichMooreLValue, ReichMoore > {

  friend BreitWignerReichMooreBase< ReichMooreLValue, ReichMoore >;

  /* auxiliary functions */

  static void
  verifyNLSC( int NLS, int NLSC ) {

    if ( NLSC < NLS ) {

      Log::error( "Encountered illegal NLSC value" );
      Log::info( "NLSC is required to be greater than or equal to NLS" );
      Log::info( "NLS value: {}", NLS );
      Log::info( "NLSC value: {}", NLSC );
      throw std::exception();
    }
  }

public:

  /* type alias */

  using LValue = ReichMooreLValue;

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ReichMoore() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lad       the angular distributions flag
   *  @param[in] nlsc      the number of l values for convergence
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  ReichMoore( double spi, double ap, bool lad, int nlsc,
              std::vector< ReichMooreLValue >&& lvalues )
    try : BreitWignerReichMooreBase( spi, ap, lad, nlsc,
                                     std::move( lvalues ) ) {

      verifyNLSC( this->NLS(), this->NLSC() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance "
                 "parameters in the Reich-Moore representation" );
      throw;
    }

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
  ReichMoore( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT )
    try : BreitWignerReichMooreBase( it, end, lineNumber, MAT, MF, MT ) {

      verifyNLSC( this->NLS(), this->NLSC() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance "
                 "parameters in the Reich-Moore representation" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 3; }

  using BreitWignerReichMooreBase::LRU;
  using BreitWignerReichMooreBase::LRF;
  using BreitWignerReichMooreBase::LFW;
  using BreitWignerReichMooreBase::averageFissionWidthFlag;

  using BreitWignerReichMooreBase::SPI;
  using BreitWignerReichMooreBase::spin;
  using BreitWignerReichMooreBase::AP;
  using BreitWignerReichMooreBase::scatteringRadius;
  using BreitWignerReichMooreBase::LAD;
  using BreitWignerReichMooreBase::angularDistributionsFlag;
  using BreitWignerReichMooreBase::NLS;
  using BreitWignerReichMooreBase::numberLValues;
  using BreitWignerReichMooreBase::NLSC;
  using BreitWignerReichMooreBase::numberLValuesForDistributions;
  using BreitWignerReichMooreBase::lValues;

  using BreitWignerReichMooreBase::NC;
  using BreitWignerReichMooreBase::print;
};
