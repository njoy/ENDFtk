template< typename Iterator >
static std::vector< LIST >
readLISTs( int NLS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LIST > lists;

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::error( "NLS value: {}", NLS );
    throw std::exception();
  }
  
  lists.reserve( NLS );
  while ( NLS-- ){ lists.emplace_back( it, end, lineNumber, MAT, MF, MT ); }
  return lists;
}

template< typename Iterator >
static std::vector< LIST >
readLISTs( const ControlRecord& cont,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  return readLISTs( cont.N1(), it, end, lineNumber, MAT, MF, MT );
}
