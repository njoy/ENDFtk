private:

/**
 *  @brief Private constructor
 */
EqualProbabilityBins( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energy   the incident energy
 *  @param[in] n2       the value for n2 (nl+1 or nu+2)
 *  @param[in] data     the data that goes into this component
 */
EqualProbabilityBins( double energy, int n2,
                      std::vector< double >&& data ) :
  ListRecord( 0., energy, 0, 0, n2, std::move( data ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
EqualProbabilityBins( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try : EqualProbabilityBins( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading equal probability distribution "
               "data (LAW=1 LANG=3)" );
    throw;
  }
