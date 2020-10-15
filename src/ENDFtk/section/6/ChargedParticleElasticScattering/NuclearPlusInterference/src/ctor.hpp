/**
 *  @brief Private constructor
 */
NuclearPlusInterference( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

private:

/**
 *  @brief Private constructor
 */
NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& values )
  try : NuclearPlusInterference( ListRecord( 0.0, energy, ltp, 0,
                                             values.size() / 2,
                                             std::move( values ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear plus interference "
               "data (LAW=5 LTP=3)" );
    throw;
  }

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energy           the incident energy value
 *  @param[in] ltp              the representation type
 *  @param[in] cosines          the cosine values
 *  @param[in] probabilities    the probability values
 */
NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& cosines,
                         std::vector< double >&& probabilities )
  try : NuclearPlusInterference(
          ListRecord( 0.0, energy, ltp, 0, cosines.size(),
                      generateList( std::move( cosines ),
                                    std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear plus interference "
               "data (LAW=5 LTP=3)" );
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
NuclearPlusInterference( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
  try : NuclearPlusInterference( ListRecord( it, end, lineNumber,
                                             MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading nuclear plus interference "
               "data (LAW=5 LTP=3)" );
    throw;
  }
