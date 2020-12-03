/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number of the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] partials      the partial distributions (at least 1)
 */
Type( int mt, double zaid, double awr,
      std::vector< PartialDistribution >&& partials ) :
  Base( zaid, awr, mt ), partials_( std::move( partials ) ) {

  verifyNK( this->NK() );
}

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
    Base( head, MAT, 5 ),
    partials_( readSequence< PartialDistribution >(
                   begin, end, lineNumber,
                   MAT, 5, head.MT(), head.N1() ) ) {
    verifyNK( this->NK() );
    readSEND( begin, end, lineNumber, MAT, 5 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 5 of Material {}",
               head.MT(), MAT );
    throw e;
  }
