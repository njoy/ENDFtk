//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
KalbachMann() = default;
#endif

private:

KalbachMann( ListRecord&& list ) :
  Base( std::move( list ) ) {

  verifyNA( this->NA() );
};

public:

/**
 *  @brief Constructor for na=1
 *
 *  @param[in] energy    the incident energy value
 *  @param[in] nd        the number of discrete energies
 *  @param[in] data      the Kalbach-Mann data (nep sets of 3 values)
 */
KalbachMann( double energy, long nd,
             std::vector< std::array< double, 3 > >&& data )
  try : KalbachMann( ListRecord( 0.0, energy, nd, 1, data.size(),
                                 generateList( std::move( data ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Kalbach-Mann distribution "
               "data (LAW=1 LANG=2)" );
    throw;
  }

/**
 *  @brief Constructor for na=2
 *
 *  @param[in] energy    the incident energy value
 *  @param[in] nd        the number of discrete energies
 *  @param[in] data      the Kalbach-Mann data (nep sets of 4 values)
 */
KalbachMann( double energy, long nd,
             std::vector< std::array< double, 4 > >&& data )
  try : KalbachMann( ListRecord( 0.0, energy, nd, 2, data.size(),
                                 generateList( std::move( data ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Kalbach-Mann distribution "
               "data (LAW=1 LANG=2)" );
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
KalbachMann( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
  try : KalbachMann( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Kalbach-Mann distribution data "
               "(LAW=1 LANG=2)" );
    throw;
  }
