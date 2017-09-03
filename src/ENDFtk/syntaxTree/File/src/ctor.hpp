File( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber )
try:
  fileNo( head.MF() ),
  sectionVector( createVector( head, begin, position, end, lineNumber) ),
  sectionMap( createMap( this->sectionVector ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  Log::info( "Trouble encountered while constructing a file syntax tree." );
  Log::info( "File number (MF): {}", head.MF() );
  throw e;
}

File( const File& other ) :
  fileNo( other.fileNo ),
  sectionVector( other.sectionVector ),
  sectionMap( createMap( this->sectionVector ) ),
  bufferLimits( other.bufferLimits ){}

File( File&& other ) noexcept = default;

