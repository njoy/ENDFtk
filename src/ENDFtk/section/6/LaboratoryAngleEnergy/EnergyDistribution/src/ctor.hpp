private:

/**
 *  @brief Private constructor
 */
EnergyDistribution( TabulationRecord&& table ) :
  TabulationRecord( std::move( table ) ) {};

public:

/**
 *  @brief Constructor
 *
 *  @param[in] cosine           the cosine value of the secondary energy
 *                              distribution
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] energies         the energy values
 *  @param[in] probabilities    the probability values
 */
EnergyDistribution( double cosine,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& energies,
                    std::vector< double >&& probabilities )
  try : EnergyDistribution(
          TabulationRecord( 0.0, cosine, 0, 0, std::move( boundaries ),
                            std::move( interpolants ), std::move( energies ),
                            std::move( probabilities ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing energy distribution data "
               "(LAW=7)" );
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
EnergyDistribution( Iterator& it, const Iterator& end,
                    long& lineNumber,
                    int MAT, int MF, int MT )
  try : EnergyDistribution( TabulationRecord( it, end, lineNumber,
                                              MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading energy distribution data "
               "(LAW=7)" );
    throw;
  }
