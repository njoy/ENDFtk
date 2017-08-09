template< typename Iterator >
static std::vector< caseCTuple >
readLists( const CONT& cont, 
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  std::vector< caseCTuple > lLists;
  auto NLS = cont.N1();

  if ( NLS < 1 ){
    Log::error( "NLS required to be positive" );
    Log::error( "NLS value: {}", NLS );
    throw std::exception();
  }

  int NJS;
  while( NLS-- ){
    CONT jCont = CONT( it, end, lineNumber, MAT, MF, MT );
    NJS = jCont.N1();
    std::vector< LIST> jLists;
    jLists.reserve( NJS );


    if ( NJS < 1 ){
      Log::error( "NJS required to be positive" );
      Log::error( "NJS value: {}", NJS );
      throw std::exception();
    }
    while( NJS-- ){
      jLists.emplace_back( it, end, lineNumber, MAT, MF, MT );
    }

    lLists.emplace_back( jCont.C1(), jCont.L1(), std::move(jLists) );
  }
  
  return lLists;
}
