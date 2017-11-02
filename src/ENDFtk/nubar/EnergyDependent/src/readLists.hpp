template< typename Iterator >
static std::vector< DecayConstant >
readLists( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT,
           int size ) {
  std::vector< DecayConstant > records;
  records.reserve( size );

  while( size-- ){
    records.emplace_back( begin, end, lineNumber, MAT, MF, MT );
    verifyNNF( records.back(), lineNumber );
  }

  return records;
}
