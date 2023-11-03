/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] lis           the level number of target
 *  @param[in] blocks        the level block subsections
 */
Type( int MT, double zaid, double awr, int lis,
      std::vector< LevelBlock >&& blocks ) :
  Base( zaid, awr, MT ), lis_( lis ),
  levelBlocks_( std::move( blocks ) ) {}

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
    Base( head, MAT, 40 ), lis_( head.L1() ),
    levelBlocks_(
      readSequence< LevelBlock >( begin, end, lineNumber,
                                  MAT, 40, head.MT(), head.N1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 40 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while reading section {} of File 40 of Material {}",
               head.MT(), MAT );
    throw e;
  }
