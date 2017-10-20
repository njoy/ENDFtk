template< typename Iterator >
static std::vector< ListRecord >
readLists( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT,
           int size ) {
  std::vector< ListRecord > records;
  records.reserve( size );

  while( size-- ){
    records.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return records;
}
