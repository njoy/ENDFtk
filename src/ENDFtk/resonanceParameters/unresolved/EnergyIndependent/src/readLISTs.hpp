template< typename Iterator >
static std::vector< LIST >
readLISTs( int NLS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LIST > lists;
  lists.reserve( NLS );

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::info( "NLS value: {}", NLS );
    throw std::exception();
  }
  while( NLS-- ){
    lists.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  return lists;
}
