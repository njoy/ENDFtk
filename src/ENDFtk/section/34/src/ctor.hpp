/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] ltt           the covariance representation
 *  @param[in] reactions     the reaction block subsections
 */
// Type( int MT, double zaid, double awr, int ltt,
//       std::vector< ReactionBlock >&& reactions ) :
//   Base( zaid, awr, MT ), ltt_( ltt ),
//   reactions_( std::move( reactions ) ) {}

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
    Base( head, MAT, 34 ), ltt_( head.L2() ),
    reactions_(
      readSequence< ReactionBlock >( begin, end, lineNumber,
                                     MAT, 34, head.MT(), head.N2() ) ) {

    readSEND(begin, end, lineNumber, MAT, 34 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while reading section {} of File 34 of Material {}",
               head.MT(), MAT );
    throw e;
  }
