File( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber )
try:
  fileNo( head.MF() ),
  sectionVector( createVector( head, begin, position, end, lineNumber) ),
  sectionMap( createMap( this->sectionVector ) ),
  bufferLimits( { begin, position } ){}
catch( std::exception& e ){
  LOG(INFO) << "Trouble encountered while constructing a file syntax tree.";
  LOG(INFO) << "File number (MF): " << head.MF();
  throw e;
}

