static std::vector< Material_t > createVector
( BufferIterator position, const BufferIterator& end, long& lineNumber ){
  std::vector< Material_t > vector;
  auto structureDivision =
    [ &position, &end, &lineNumber ](){
    return StructureDivision( position, end, lineNumber );
  };

  auto begin = position;
  auto division = structureDivision();
  vector.emplace_back( asHead( division ), begin, position, end, lineNumber );
  begin = position;
  if( position >= end ){
    LOG(ERROR) <<
      "Tape encountered end of stream before reading TEND record";
    throw std::exception();
  }

  while( ( division = structureDivision() ).isHead() ){
    vector.emplace_back( asHead( division ), begin, position, end, lineNumber );
    begin = position;
    if( position >= end ){
      LOG(ERROR) <<
        "Tape encountered end of stream before reading TEND record";
      throw std::exception();
    }
  }
  
  if( not division.isTend() ){
    LOG(ERROR) << "TEND record is misformatted";
    utility::echoErroneousLine(begin, begin, end, lineNumber );
    throw std::exception();
  }
  
  return vector;
}
