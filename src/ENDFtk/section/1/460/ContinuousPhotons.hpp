/**
 *  @class
 *  @brief Continuous delayed photon decay constants
 *
 *  See ENDF102, section 1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT ContinuousPhotons : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL ) {

    if ( NPL <= 0 ) {

      Log::error( "Inconsistent data size" );
      Log::info( "Expected NNF > 0" );
      Log::info( "NNF value: {}", NPL );
      throw std::exception();
    }
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ContinuousPhotons() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy        the incident neutron energy
   *  @param[in] constants     the precursor families decay constants
   */
  ContinuousPhotons( std::vector< double >&& constants )
    try : ListRecord( 0.0, 0.0, 0, 0, 0, std::move( constants ) ) {

      verifySize( this->NNF() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing continuous delayed photon "
                 "data" );
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
  ContinuousPhotons( Iterator& begin, const Iterator& end,
                     long& lineNumber, int MAT, int MF, int MT )
    try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {

      verifySize( this->NNF() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing continuous delayed photon "
                 "data" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  static constexpr int LO() { return 2; }

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the number of discrete photons
   */
  static constexpr int NG() { return 0; }

  /**
   *  @brief Return the number of discrete photons
   */
  int numberDiscretePhotons() const { return this->NG(); }

  /**
   *  @brief Return the number of precursor families
   */
  int NNF() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of precursor families
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the decay constants for all precursor families
   */
  auto lambdas() const { return ListRecord::list(); }

  /**
   *  @brief Return the decay constants for all precursor families
   */
  auto decayConstants() const { return this->lambdas(); }

  using ListRecord::NC;
  using ListRecord::print;
};
