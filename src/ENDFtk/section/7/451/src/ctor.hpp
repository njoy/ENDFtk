/**
 *  @brief Constructor
 *
 *  @param[in] zaid       the ZA  identifier
 *  @param[in] awr        the atomic mass ratio
 *  @param[in] elements   the elements (at least 1)
 */
Type( int zaid, double awr, std::vector< ElementInformation >&& elements ) :
  BaseWithoutMT( zaid, awr ), elements_( std::move( elements ) ) {

  verifySize( this->NA() );
}

/**
 *  @brief Constructor for a single element
 *
 *  @param[in] zaid       the ZA  identifier
 *  @param[in] awr        the atomic mass ratio
 *  @param[in] element    the element information
 */
Type( int zaid, double awr, ElementInformation&& element ) :
  Type( zaid, awr, std::vector< ElementInformation >{ std::move( element ) } ) {}

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
  try: Type( head.ZA(), head.AWR(),
             readSequence< ElementInformation >( begin, end, lineNumber,
                                                 MAT, 7, head.MT(), head.L1() ) ) {

    readSEND(begin, end, lineNumber, MAT, 7 );
  }
  catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 7 of material {}",
      head.MT(), MAT );
    throw e;
  }
