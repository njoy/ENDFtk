/**
 *  @brief Constructor
 *
 *  @param[in] energy          the incident energy value
 *  @param[in] nd              the number of discrete energies
 *  @param[in] na              the number of angular parameters
 *  @param[in] energies        the energy values
 *  @param[in] coefficients    the Legendre coefficients
 */
LegendreCoefficients( double energy, long nd, long na,
                      std::vector< double > energies,
                      std::vector< std::vector< double > >&& coefficients )
  try : Base( energy, nd, na, energies.size(),
              generateList( na, std::move( energies ),
              std::move( coefficients ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Legendre coefficients "
               "(LAW=1 LANG=1)" );
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
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try : Base( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Legendre coefficients "
               "(LAW=1 LANG=1)" );
    throw;
  }
