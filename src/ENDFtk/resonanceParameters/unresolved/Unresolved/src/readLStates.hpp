template< typename Iterator >
static std::vector< LState >
readLStates( int NLS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< LState > lists;
  lists.reserve( NLS );

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::info( "NLS value: {}", NLS );
    throw std::exception();
  }
  while( NLS-- ){
    lists.emplace_back( CONT( it, end, lineNumber, MAT, MF, MT ),
                        it, end, lineNumber, MAT, MF, MT );
  }
  return lists;
}
