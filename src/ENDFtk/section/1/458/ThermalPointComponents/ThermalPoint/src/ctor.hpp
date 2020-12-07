/**
 *  @brief Private constructor
 */
ThermalPointComponents( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verify( ListRecord::NPL() );
  }

public:

/**
 *  @brief Constructor
 *
 *  @param[in] ldrv            the primary evaluation flag (true/false)
 *  @param[in] ifc             the index for the fission energy release
 *                             component
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the incident energy values
 *  @param[in] qvalues         the fission q values
 */
ThermalPointComponents( bool ldrv, int ifc,
                        std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< double >&& energies,
                        std::vector< double >&& qvalues )
  try : ThermalPointComponents(
            TabulationRecord( 0.0, 0.0, ldrv ? 2 : 1, ifc,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( energies ),
                              std::move( qvalues ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a thermal point "
               "evaluation" );
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
ThermalPointComponents( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
  try : EnergyReleaseComponent(
            ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a thermal point "
               "evaluation" );
    throw;
  }
