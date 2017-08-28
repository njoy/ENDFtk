template< typename Iterator >
static std::vector< LIST >
readLists( int NJS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LIST > lists;

  if ( NJS < 0 ){
    Log::error( "Encountered illegal NJS value" );
    Log::info( "NJS required to greater than or equal to zero" );
    Log::info( "NJS value: {}", NJS );
    throw std::exception();
  }

  lists.reserve( NJS );

  while( NJS-- ){
    lists.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  
  return lists;
}
