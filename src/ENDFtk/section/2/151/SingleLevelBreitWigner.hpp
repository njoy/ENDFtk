/**
 *  @class
 *  @brief Single level Breit-Wigner resonance parameters
 *
 *  The SingleLevelBreitWigner class is used to represent the SLBW
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT SingleLevelBreitWigner :
  protected BreitWignerReichMooreBase< BreitWignerLValue,
                                       SingleLevelBreitWigner > {

  friend BreitWignerReichMooreBase< BreitWignerLValue, SingleLevelBreitWigner >;

public:

  /* type alias */

  using LValue = BreitWignerLValue;

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  SingleLevelBreitWigner() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  SingleLevelBreitWigner( double spi, double ap,
                          std::vector< BreitWignerLValue >&& lvalues )
    try : BreitWignerReichMooreBase( spi, ap, false, 0,
                                     std::move( lvalues ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance "
                 "parameters in the Single Level Breit-Wigner representation" );
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
  SingleLevelBreitWigner( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT )
    try : BreitWignerReichMooreBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance "
                 "parameters in the Single Level Breit-Wigner representation" );
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
  static constexpr int representation() { return 1; }

  using BreitWignerReichMooreBase::LRU;
  using BreitWignerReichMooreBase::LRF;
  using BreitWignerReichMooreBase::LFW;
  using BreitWignerReichMooreBase::averageFissionWidthFlag;

  using BreitWignerReichMooreBase::SPI;
  using BreitWignerReichMooreBase::spin;
  using BreitWignerReichMooreBase::AP;
  using BreitWignerReichMooreBase::scatteringRadius;
  using BreitWignerReichMooreBase::NLS;
  using BreitWignerReichMooreBase::numberLValues;
  using BreitWignerReichMooreBase::lValues;

  using BreitWignerReichMooreBase::NC;
  using BreitWignerReichMooreBase::print;
};
