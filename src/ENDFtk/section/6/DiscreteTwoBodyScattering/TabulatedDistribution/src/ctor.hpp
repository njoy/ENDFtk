//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
TabulatedDistribution() = default;
#endif

/**
 *  @brief Private constructor
 */
TabulatedDistribution( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the incident energy value
 *  @param[in] lang            the interpolation type for the distribution
 *  @param[in] energies        the cosine values
 *  @param[in] probabilities   the probability values
 */
TabulatedDistribution( double incident, int lang,
                       std::vector< double >&& cosines,
                       std::vector< double >&& probabilities )
  try : TabulatedDistribution( ListRecord( 0.0, incident, lang, 0,
                                           cosines.size(),
                                           generateList( std::move( cosines ),
                                                         std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG={})", lang );
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
TabulatedDistribution( Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT )
  try : TabulatedDistribution( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG=12/14)" );
    throw;
  }
