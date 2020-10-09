/**
 *  @brief Constructor
 *
 *  @param[in] mt              the MT number for the section
 *  @param[in] zaid            the material ZAID value
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] lct             the reference frame
 *  @param[in] distributions   the distributions
 */
Type( int MT, double zaid, double awr, long lct,
      Distributions&& distributions ) :
  Base( zaid, awr, MT ), lct_( lct ),
  distributions_( std::move( distributions ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
Type ( HEAD& head,
       const ControlRecord& cont,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT ) :
  Base( head, MAT, 4 ),
  lct_( cont.L2() ),
  distributions_( readDistributions( begin, end, lineNumber,
                                     head.MAT(), 4, head.MT(), head.L2() ) ) {}

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
Type ( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Type( head,
             ControlRecord( begin, end, lineNumber, head.MAT(), 4, head.MT() ),
             begin, end, lineNumber, MAT ) {

    readSEND(begin, end, lineNumber, MAT, 4 );
  } catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 4 of material {}",
      head.MT(), MAT );
    throw;
  }
