template< typename Iterator >
static std::vector< LIST >
readLists( int NJS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  Log::info("NJS: {}", NJS);
  if ( NJS < 1 ){
    Log::error( "NJS required to be positive" );
    Log::error( "NJS value: {}", NJS );
    throw std::exception();
  }

  std::vector< LIST > lists;
  lists.reserve( NJS );

  while( NJS-- ){
    lists.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  return lists;
}
