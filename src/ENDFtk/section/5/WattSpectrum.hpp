/**
 *  @class
 *  @brief The Watt fission spectrum (LF=11)
 *
 *  See ENDF102, section 5.1.1.5 and 5.2.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT WattSpectrum {

  std::array< Parameter, 2 > parameters_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::array< Parameter, 2 >
  readParameters( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT ) {

    auto makeParameter = [&] ( auto&& message ) {

      try {

        return Parameter( begin, end, lineNumber, MAT, MF, MT );
      }
      catch ( ... ) {

        Log::info( message );
        throw;
      }
    };

    auto a = makeParameter( "Encountered error while reading the a parameter" );
    auto b = makeParameter( "Encountered error while reading the b parameter" );
    return std::array< Parameter, 2 >{{ std::move( a) , std::move( b ) }};
  }

  /* constructor */

  /**
   *  @brief Protected Constructor
   */
  WattSpectrum( std::array< Parameter, 2 >&& parameters ) :
    // no need to try-catch, would be unreachable
    parameters_( std::move( parameters ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  WattSpectrum() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] a   the parameter function a
   *  @param[in] a   the parameter function b
   */
   WattSpectrum( Parameter&& a, Parameter&& b ) :
     // no need to try-catch, would be unreachable
     parameters_( {{ std::move( a ), std::move( b ) }} ) {}

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
  WattSpectrum( Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int MF,
                     int MT )
    try : WattSpectrum( readParameters( begin, end, lineNumber,
                                        MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading a Watt spectrum" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 11; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the a parameter data
   */
  const Parameter& a() const { return this->parameters_[0]; }

  /**
   *  @brief Return the b parameter data
   */
  const Parameter& b() const { return this->parameters_[1]; }

  /** 
   *  @brief Return the number of lines in this MF5 component
   */
  long NC() const {

    return this->parameters_[0].NC() + this->parameters_[1].NC();
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

    for ( const auto& entry : this->parameters_ ) { entry.print( it, MAT, MF, MT ); };
  } 
};
