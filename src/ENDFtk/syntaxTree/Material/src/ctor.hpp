Material( const HEAD& head, BufferIterator begin, BufferIterator& position,
          const BufferIterator& end, long& lineNumber )
try:
  materialNo( head.MAT() ),
  fileVector( createVector( head, begin, position, end, lineNumber) ),
  fileMap( createMap( this->fileVector ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  Log::info( "Trouble encountered while constructing a material syntax tree." );
  Log::info( "Material number (MAT): {}", head.MAT() );
  throw e;
}

Material( const Material& other ) :
  materialNo( other.materialNo ),
  fileVector( other.fileVector ),
  fileMap( createMap( this->fileVector ) ),
  bufferLimits( other.bufferLimits ){}

Material( Material&& other ) noexcept :
  materialNo( other.materialNo ),
  fileVector( std::move( other.fileVector ) ),
  fileMap( createMap( this->fileVector ) ),
  bufferLimits( other.bufferLimits ){}
