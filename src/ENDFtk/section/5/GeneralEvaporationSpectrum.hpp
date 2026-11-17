/**
 *  @class
 *  @brief The general evaporation spectrum (LF=5)
 *
 *  See ENDF102, section 5.1.1.2 and 5.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT GeneralEvaporationSpectrum {

  EffectiveTemperature temperature_;
  DistributionFunction distribution_;

  /* constructor */

  template< typename Iterator >
  GeneralEvaporationSpectrum( EffectiveTemperature&& temperature,
                              Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
    GeneralEvaporationSpectrum( std::move( temperature ),
                                DistributionFunction( begin, end, lineNumber,
                                MAT, MF, MT ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  GeneralEvaporationSpectrum() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] temperature    the effective temperature
   *  @param[in] distribution   the distribution function g(x)
   */
  GeneralEvaporationSpectrum( EffectiveTemperature&& temperature,
                              DistributionFunction&& distribution ) :
    // no need to try-catch, would be unreachable
    temperature_( std::move( temperature ) ),
    distribution_( std::move( distribution ) ) {}

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
  GeneralEvaporationSpectrum( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT )
    try : GeneralEvaporationSpectrum(
              EffectiveTemperature( begin, end, lineNumber, MAT, MF, MT ),
              begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading a general evaporation "
                 "spectrum" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 5; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the effective temperature
   */
  const EffectiveTemperature& theta() const { return this->temperature_; }

  /**
   *  @brief Return the effective temperature
   */
  const EffectiveTemperature& effectiveTemperature() const {

    return this->theta();
  }

  /**
   *  @brief Return the distribution function g(x)
   */
  const DistributionFunction& g() const { return this->distribution_; }

  /**
   *  @brief Return the distribution function g(x)
   */
  const DistributionFunction& distributionFunction() const { return this->g(); }

  /** 
   *  @brief Return the number of lines in this MF5 component
   */
  long NC() const {
    return this->temperature_.NC() + this->distribution_.NC();
  };

  /** 
   *  @brief Print this MF5 component
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

    this->temperature_.print( it, MAT, MF, MT );
    this->distribution_.print( it, MAT, MF, MT );
  } 
};
