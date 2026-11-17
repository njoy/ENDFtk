/**
 *  @class
 *  @brief Special case: no parameters are given (LRU=0, LRF=0)
 *
 *  The SpecialCase class is used to represent the special case where only
 *  the spin and scattering radius are given in MF2/MT151.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT SpecialCase {

  /* fields */

  double spi_;
  double ap_;

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  SpecialCase( ControlRecord&& cont ) :
    SpecialCase( cont.C1(), cont.C2() ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  SpecialCase() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi   the target spin
   *  @param[in] ap    the scattering radius
   */
  SpecialCase( double spi, double ap ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ) {}

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
  SpecialCase( Iterator& it, const Iterator& end, long& lineNumber,
               int MAT, int MF, int MT )
    try : SpecialCase( ControlRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing the special case without "
                 "resonance parameters" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 0; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return SpecialCase::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 0; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return SpecialCase::LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  static constexpr bool LFW() { return false; }

  /**
   *  @brief Return the average fission flag
   */
  static constexpr bool averageFissionWidthFlag() { return SpecialCase::LFW(); }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return 1; }

  /**
   *  @brief Print this MF2 MT151 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    ControlRecord( this->SPI(), this->AP(), 0, 0, 0, 0 ).print( it, MAT, MF, MT );
  }
};
