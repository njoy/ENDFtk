/**
 *  @brief Constructor
 *
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] subsections   the partial distributions (at least 1)
 */
Type( int MT, double zaid, double awr,
      std::vector< SubSection >&& subsections ) :
  Base( zaid, awr, MT ), subsections_( std::move( subsections ) ) {

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
    subsections_( readSubSections( begin, end, lineNumber,
                                   MAT, 5, head.MT(), head.N1() ) ) {
    verifyNK( this->NK() );
    readSEND( begin, end, lineNumber, MAT, 5 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 5 of Material {}",
               head.MT(), MAT );
    throw e;
  }

