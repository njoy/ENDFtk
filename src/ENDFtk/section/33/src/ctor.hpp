/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] mtl           the lumped covariance index
 *  @param[in] subsections   the subsections
 */
Type( int MT, double zaid, double awr, long mtl,
      std::vector< Subsection >&& subsections ) :
  Base( zaid, awr, MT ), mtl_( mtl ),
  subsections_( std::move( subsections ) ) {}

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
    Base( head, MAT, 33 ), mtl_( head.L2() ),
    subsections_(
      readSequence< Subsection >( begin, end, lineNumber,
                                  MAT, 33, head.MT(), head.N1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 6 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while reading section {} of File 33 of Material {}",
               head.MT(), MAT );
    throw e;
  }
