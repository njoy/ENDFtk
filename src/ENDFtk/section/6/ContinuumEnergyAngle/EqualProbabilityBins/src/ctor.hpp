private:

/**
 *  @brief Private constructor
 */
EqualProbabilityBins( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {}

public:

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
