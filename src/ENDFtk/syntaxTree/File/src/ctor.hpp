File( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber )
try:
  fileNo( head.MF() ),
  sections_( createMap( head, begin, position, end, lineNumber ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  Log::info( "Trouble encountered while constructing a file syntax tree." );
  Log::info( "File number (MF): {}", head.MF() );
  throw e;
}

/*
File( const File& other ) 
try:
  fileNo( other.fileNo ),
  sections_( other.sections_ ),
  bufferLimits( other.bufferLimits ){}
catch( std::exception&  ){
  Log::info( 
      "Trouble encountered while copy constructing a syntaxTree::File." );
  throw;
}

File( File&& other ) noexcept = default;

*/
