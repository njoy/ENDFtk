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
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] jp            the particle spectrum type flag
 *  @param[in] lct           the reference frame
 *  @param[in] products      the reaction products (at least 1)
 */
Type( int MT, int zaid, double awr, long jp, long lct,
      std::vector< ReactionProduct >&& products ) :
  Base( zaid, awr, MT ), jp_( jp ), lct_( lct ),
  products_( std::move( products ) ) {}

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
Type( HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT )
  try:
    Base( head, MAT, 6 ), jp_( head.L1() ), lct_( head.L2() ),
    products_(
      readSequence< ReactionProduct >( begin, end, lineNumber,
                                       MAT, 6, head.MT(), head.N1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 6 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while reading section {} of File 6 of Material {}",
               head.MT(), MAT );
    throw e;
  }
