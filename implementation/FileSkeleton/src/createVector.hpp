static std::vector< SectionSkeleton_t >
createVector
( const HeadRecord& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::vector< SectionSkeleton_t > vector;
  vector.emplace_back( head, begin, position, end, lineNumber );
  begin = position; 
  auto division = StructureDivision( position, end, lineNumber );
  while( division.isHead() ){
    vector.emplace_back( asHead(division), begin, position, end, lineNumber );
    if( position >= end ){
      LOG(ERROR) <<
        "File encountered end of stream before reading FEND record";
      throw std::exception();
    }

    begin = position; 
    division = StructureDivision( position, end, lineNumber );  
  }

  if( not division.isFend() ){
    LOG(ERROR) << "FEND record is misformatted";
    utility::echoErroneousLine(begin, begin, end, lineNumber );
    throw std::exception();
  }
  
  return vector;
}
