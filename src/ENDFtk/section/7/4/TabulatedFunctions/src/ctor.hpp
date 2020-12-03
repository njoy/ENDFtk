private:
/**
 *  @brief Private constructor
 */
TabulatedFunctions( InterpolationSequenceRecord< ScatteringFunction >&& sequence ) :
  data_( std::move( sequence ) ) {

  //! @todo verify number of beta versus NB
  //! @todo verify the same temperature in each ScatteringFunction
  //! @todo verify the same temperature interpolants in each ScatteringFunction
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] functions      the beta values and associated S(alpha,T)
 *                            functions
 */
TabulatedFunctions( std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< ScatteringFunction >&& functions )
  try : TabulatedFunctions( InterpolationSequenceRecord< ScatteringFunction >(
                              InterpolationRecord( 0.0, 0.0, 0, 0,
                                                   std::move( boundaries ),
                                                   std::move( interpolants ) ),
                              std::move( functions ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing tabulated thermal "
               "scattering law" );
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
TabulatedFunctions( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT )
  try : TabulatedFunctions(
          ENDFtk::readInterpolationSequenceRecord< ScatteringFunction >(
              begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing tabulated thermal "
               "scattering law" );
    throw;
  }
