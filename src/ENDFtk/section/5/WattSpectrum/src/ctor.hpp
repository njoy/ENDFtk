protected:

/**
 *  @brief Protected Constructor
 */
WattSpectrum( std::array< Parameter, 2 >&& parameters ) :
  // no need to try-catch, would be unreachable
  parameters_( std::move( parameters ) ) {}

public :
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
