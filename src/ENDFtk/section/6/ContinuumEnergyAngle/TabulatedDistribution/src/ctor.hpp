private:
  /**
   *  @brief Private constructor
   */
TabulatedDistribution( int lang, ListRecord&& list ) :
  Base( std::move( list ) ), lang_( lang ) {

  checkLANG( this->LANG() );
};

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energy           the incident energy value
 *  @param[in] nd               the number of discrete energies
 *  @param[in] na               the number of angular parameters
 *  @param[in] energies         the energy values
 *  @param[in] emissions        the total emission probabilities
 *  @param[in] cosines          the energy values
 *  @param[in] probabilities    the Legendre coefficients
 */
TabulatedDistribution( int lang, double energy, long nd, long na,
                       std::vector< double >&& energies,
                       std::vector< double >&& emissions,
                       std::vector< std::vector< double > >&& cosines,
                       std::vector< std::vector< double > >&& probabilities )
  try : TabulatedDistribution(
            lang,
            ListRecord( 0.0, energy, nd, na, energies.size(),
                        generateList( na,
                                      std::move( energies ),
                                      std::move( emissions ),
                                      std::move( cosines ),
                                      std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing tabulated distribution "
               "data (LAW=1 LANG={})", lang );
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
TabulatedDistribution( int lang, Iterator& it, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
  try : TabulatedDistribution( lang, ListRecord( it, end, lineNumber,
                                                 MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=1 LANG={})", lang );
    throw;
  }
