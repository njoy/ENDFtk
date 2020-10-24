/**
 *  @brief Constructor (from a buffer)
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] head         the first head record of the file
 *  @param[in] begin        the beginning of the buffer
 *  @param[in] position     the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
File( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber )
  try: materialNo( head.MAT() ),
       fileNo( head.MF() ),
       sections_( createMap( head, begin, position, end, lineNumber ) ),
       bufferLimits( { begin, position } ) {}
  catch( std::exception& e ) {

    Log::info( "Trouble encountered while constructing a file syntax tree." );
    Log::info( "File number (MF): {}", head.MF() );
    throw e;
  }
