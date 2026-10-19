/**
 *  @class
 *  @brief Energy independent decay constants for delayed neutron precursor
 *         families (LDG = 0)
 *
 *  See ENDF102, section 1.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyIndependentConstants : protected ListRecord {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  EnergyIndependentConstants() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] constants    the precursor families decay constants
   */
  EnergyIndependentConstants( std::vector< double >&& constants )
    try : ListRecord( 0.0, 0.0, 0, 0, 0,
                      std::move( constants ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing energy independent "
      	         "decay constant for delayed neutron precursors" );
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
  EnergyIndependentConstants( Iterator& begin, const Iterator& end,
                              long& lineNumber, int MAT, int MF, int MT )
    try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing energy independent "
      	         "decay constant for delayed neutron precursors" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the type of decay constants
   */
  static constexpr int LDG() { return 0; }

  /**
   *  @brief Return the type of decay constants
   */
  int type() const { return this->LDG(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the decay constants
   */
  auto lambdas() const { return ListRecord::list(); }

  /**
   *  @brief Return the decay constants
   */
  auto decayConstants() const { return this->lambdas(); }

  using ListRecord::NC;
  using ListRecord::print;
};
