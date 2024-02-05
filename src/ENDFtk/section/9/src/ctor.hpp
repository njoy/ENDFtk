//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] mt         the MT number
 *  @param[in] zaid       the ZA  identifier
 *  @param[in] awr        the atomic mass ratio
 *  @param[in] lis        the target's excited level
 *  @param[in] products   the reaction products (at least 1)
 */
Type( int mt, int zaid, double awr, long lis,
      std::vector< ReactionProduct >&& products ) :
  Base( zaid, awr, mt ), lis_( lis ), products_( std::move( products ) ) {}

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
  try: Type( head.MT(), head.ZA(), head.AWR(), head.L1(),
             readSequence< ReactionProduct >( begin, end, lineNumber,
                                              MAT, 9, head.MT(), head.N1() ) ) {

    readSEND(begin, end, lineNumber, MAT, 9 );
  }
  catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 9 of material {}",
      head.MT(), MAT );
    throw e;
  }
