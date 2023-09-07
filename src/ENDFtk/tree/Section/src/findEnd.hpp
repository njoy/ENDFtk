template< typename BufferIterator >
static BufferIterator findEnd
( BufferIterator& position, const BufferIterator& end, long& lineNumber ) {

  // skip to the first SEND record
  while ( record::skip( position, end, lineNumber ).MT() != 0 ) {

    if ( position >= end ) {

      Log::error( "Encountered the end of stream before a SEND record was found" );
      throw std::exception();
    }
  }
  return position;
}
