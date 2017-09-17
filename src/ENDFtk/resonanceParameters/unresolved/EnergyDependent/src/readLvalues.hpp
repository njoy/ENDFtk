template< typename Iterator >
static std::vector< Lvalue >
readLvalues( int NLS,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) {
  std::vector< Lvalue > lValues;

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::error( "NLS value: {}", NLS );
    throw std::exception();
  }
  
  lValues.reserve( NLS );
  while ( NLS-- ){ lValues.emplace_back( it, end, lineNumber, MAT, MF, MT ); }
  return lValues;
}
