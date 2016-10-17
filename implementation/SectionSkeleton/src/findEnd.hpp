static BufferIterator
findEnd
( BufferIterator& position, const BufferIterator& end, long& lineNumber ){
  while( record::skip( position, end, lineNumber ).MT() != 0 ){
    if( position >= end ){
      LOG(ERROR) << "Section encountered end of stream before reading SEND";
      throw std::exception();
    }
  }
  return position;
}
