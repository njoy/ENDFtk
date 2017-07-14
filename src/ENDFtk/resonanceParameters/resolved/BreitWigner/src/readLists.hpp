template< typename Iterator >
static std::vector< LIST >
readLists( const CONT& cont,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LIST > lists;
  auto NLS = cont.N1();

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::error( "NLS value: {}", NLS );
    throw std::exception();
  }
  
  lists.reserve( NLS );
  while ( NLS-- ){ lists.emplace_back( it, end, lineNumber, MAT, MF, MT ); }
  return lists;
}
