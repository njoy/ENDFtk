Material( const HEAD& head, BufferIterator begin, BufferIterator& position,
          const BufferIterator& end, long& lineNumber )
try:
  materialNo( head.MAT() ),
  files_( createMap( head, begin, position, end, lineNumber ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  Log::info( "Trouble encountered while constructing a material syntax tree." );
  Log::info( "Material number (MAT): {}", head.MAT() );
  throw e;
}

/*
Material( const Material& other )
try:
  materialNo( other.materialNo ),
  files_( other.files_ ),
  bufferLimits( other.bufferLimits ){}
catch( std::exception&  ){
  Log::info( 
      "Trouble encountered while copy constructing a syntaxTree::Material." );
  throw;
}

Material( Material&& other ) noexcept = default;
*/
