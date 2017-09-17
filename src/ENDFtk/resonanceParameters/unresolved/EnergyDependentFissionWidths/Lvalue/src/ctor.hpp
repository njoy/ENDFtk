public:
Lvalue( double AWRI, int L, std::vector< LIST >&& lists ) :
  lists( std::move(lists) ), awri( AWRI ), l( L ) {}

protected:
template< typename Iterator >
Lvalue( CONT&& cont,
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) : 
    Lvalue( cont.C1(), cont.L1(),
            readLISTs( cont.N1(), it, end, lineNumber, MAT, MF, MT ) ){}

public:
template< typename Iterator >
Lvalue( Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try:
    Lvalue( CONT( it, end, lineNumber, MAT, MF, MT ),
            it, end, lineNumber, MAT, MF, MT ) {
  } catch( std::exception& e ) {
    Log::info( "Trouble encountered when parsing Lvalue" );
    throw e;
  }
