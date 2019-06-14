/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] thetas          the theta values
 */
MaxwellianFissionSpectrum( std::vector< long >&& boundaries,
                           std::vector< long >&& interpolants,
                           std::vector< double >&& energies,
                           std::vector< double >&& thetas )
  try : EffectiveTemperature( std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( energies ),
                              std::move( thetas ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while constructing a Maxwellian fission "
               "spectrum" );
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
MaxwellianFissionSpectrum( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
  try : EffectiveTemperature( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Error encountered while reading a Maxwellian fission "
               "spectrum" );
    throw;
  }

//! @todo the following code was supposed to replace the current constructors
//!       this one does not play nice with brace initilisation and no solution
//!       has been found
// /**
//  *  @brief Constructor
//  *
//  *  You can construct a MaxwellianFissionSpectrum using any constructor for
//  *  EffectiveTemperature (including copy, move, etc. constructors).
//  */
// template< typename... Args,
//           std::enable_if_t
//           < std::is_constructible
//             < EffectiveTemperature, Args... >::value,
//             bool > = false >
// MaxwellianFissionSpectrum( Args&&... args )
//   try : EffectiveTemperature( std::forward< Args >( args )... ) {}
//   catch ( std::exception& e ) {
//
//     Log::info( "Error encountered while constructing a Maxwellian fission "
//                "spectrum" );
//     throw;
//   }
//
