template< typename Iterator >
static std::vector< LIST >
readLists( int NJS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LIST > lists;
  lists.reserve( NJS );

  if ( NJS < 0 ){
    Log::error( "NJS required to >= 0" );
    Log::error( "NJS value: {}", NJS );
    throw std::exception();
  }

  while( NJS-- ){
    lists.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  return lists;
}
