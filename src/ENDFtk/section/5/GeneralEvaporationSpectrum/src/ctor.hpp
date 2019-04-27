/** 
 *  @brief Constructor
 *
 *  @param[in] temperature    the effective temperature
 *  @param[in] distribution   the distribution function g(x)
 */
GeneralEvaporationSpectrum( EffectiveTemperature&& temperature,
                            Parameter&& distribution ) :
  // no need to try-catch, would be unreachable
  temperature_( std::move( temperature ) ),
  distribution_( std::move( distribution ) ) {}

protected:

template< typename Iterator >
GeneralEvaporationSpectrum( EffectiveTemperature&& temperature,
                            Iterator& begin,
                            const Iterator& end,
                            long& lineNumber,
                            int MAT,
                            int MF,
                            int MT ) :
  GeneralEvaporationSpectrum( std::move( temperature ),
                              Parameter( begin, end, lineNumber, MAT, MF, MT ) ) {}

public:
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
