public:
template< typename Iterator >
LState( const CONT& cont, 
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try:
    lists( readLists( cont.N1(), it, end, lineNumber, MAT, MF, MT ) ),
    awri( cont.C1() ),
    l( cont.L1() )
  {
  } catch( std::exception& e ){
    Log::info( "Trouble encountered when creating LState" );
    throw e;
  }
