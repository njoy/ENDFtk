Material( const HEAD& head, BufferIterator begin, BufferIterator& position,
          const BufferIterator& end, long& lineNumber )
try:
  materialNo( head.MAT() ),
  fileVector( createVector( head, begin, position, end, lineNumber) ),
  fileMap( createMap( this->fileVector ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  LOG(INFO) << "Trouble encountered while constructing a material syntax tree.";
  LOG(INFO) << "Material number (MAT): " << head.MAT();
  throw e;
}
