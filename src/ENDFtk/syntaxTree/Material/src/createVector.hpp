static std::vector< File_t > createVector
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::vector< File_t > vector;
  vector.emplace_back( head, begin, position, end, lineNumber );
  begin = position;
  auto division = StructureDivision( position, end, lineNumber ); 

  while( division.isHead() ){
    vector.emplace_back( asHead(division), begin, position, end, lineNumber );
    if( position >= end ){
      LOG(ERROR) <<
        "Material encountered end of stream before reading MEND record";
      throw std::exception();
    }
    begin = position;
    division = StructureDivision( position, end, lineNumber );  
  }

  if( not division.isMend() ){
    LOG(ERROR) << "MEND record is misformatted";
    utility::echoErroneousLine(begin, begin, end, lineNumber );
    throw std::exception();
  }
  return vector;
}
