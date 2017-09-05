template< typename BufferIterator >
static std::vector< Section > collectVector( StructureDivision& division,
                                             BufferIterator& begin,
                                             const BufferIterator& end,
                                             long& lineNumber ){
  std::vector< Section > sectionVector;
  while( not division.isFend() ){
    sectionVector.emplace_back( asHead(division),
                                begin, end, lineNumber,
                                division.tail.MAT() );
    division = StructureDivision( begin, end, lineNumber );
  }
  return sectionVector;
}
