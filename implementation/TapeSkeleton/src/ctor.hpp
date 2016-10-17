TapeSkeleton
( BufferIterator& begin, const BufferIterator& end, long lineNumber = 0 )
try:
  bufferLimits( { begin, end } ),
  tpid( begin, end, lineNumber ),
  materialVector( createVector( begin, end, lineNumber ) ),
  materialMap( createMap( this->materialVector ) ){}
catch ( std::exception& e ){
  LOG(INFO) << "Trouble encountered while constructing a TapeSkeleton.";
  throw e;
}
