template< typename Iterator >
static std::vector< LIST >
readLists( int NJS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  if ( NJS < 0 ){
    Log::error( "NJS required to >= 0" );
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
