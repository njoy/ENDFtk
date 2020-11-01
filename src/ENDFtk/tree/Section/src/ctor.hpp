/**
 *  @brief Constructor (from a buffer)
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the beginning of the buffer
 *  @param[in] position     the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
Section( const HEAD& head, BufferIterator begin,
         BufferIterator& position, const BufferIterator& end,
         long& lineNumber )
  try: materialNo( head.MAT() ),
       fileNo( head.MF() ),
       sectionNo( head.MT() ),
       bufferLimits( { begin, findEnd( position, end, lineNumber ) } ) {}
  catch( std::exception& e ) {

    Log::info( "Trouble when creating a syntaxTree::Section" );
    Log::info( "File/section number (MF/MT) corresponding "
               "to erroneous section: {}/{}",
               head.MF(), head.MT() );
    throw e;
  }
