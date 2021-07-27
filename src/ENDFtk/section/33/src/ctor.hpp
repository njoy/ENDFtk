/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] reactions     the reaction block subsections
 */
Type( int MT, double zaid, double awr,
      std::vector< ReactionBlock >&& reactions ) :
  Base( zaid, awr, MT ), mtl_( 0 ),
  reactions_( std::move( reactions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] mtl           the lumped covariance index
 */
Type( int MT, double zaid, double awr, int mtl ) :
  Base( zaid, awr, MT ), mtl_( mtl ) {}

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
    reactions_(
      readSequence< ReactionBlock >( begin, end, lineNumber,
                                  MAT, 33, head.MT(), head.N2() ) ) {
    readSEND(begin, end, lineNumber, MAT, 33 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while reading section {} of File 33 of Material {}",
               head.MT(), MAT );
    throw e;
  }
