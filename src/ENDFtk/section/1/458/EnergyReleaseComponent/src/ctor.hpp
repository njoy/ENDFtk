private:

/**
 *  @brief Private constructor
 */
EnergyReleaseComponent( TabulationRecord&& table ) :
  TabulationRecord( std::move( table ) ) {

    verify( TabulationRecord::L1(), TabulationRecord::L2() );
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
EnergyReleaseComponent( bool ldrv, int ifc,
                        std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< double >&& energies,
                        std::vector< double >&& qvalues )
  try : EnergyReleaseComponent(
            TabulationRecord( 0.0, 0.0, ldrv ? 2 : 1, ifc,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( energies ),
                              std::move( qvalues ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a tabulated fission "
    	         "energy release component" );
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
EnergyReleaseComponent( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
  try : EnergyReleaseComponent(
            TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a tabulated fission "
    	         "energy release component" );
    throw;
  }
