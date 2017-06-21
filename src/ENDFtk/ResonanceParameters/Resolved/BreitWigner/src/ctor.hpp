
BreitWigner( Base&& base, TAB1&& tab1, CONT&& cont, LIST&& list ) :
  Base( std::move( base) ),
  tab1( std::move( tab1 ) ),
  cont( std::move( cont ) ),
  list( std::move( list ) ){
  try {
  } catch( std::exception& e ){
    Log::info( "Encountered error while parsing ENDF BreitWigner subsection" );
    throw e;
  }
}

BreitWigner( Base&& base, CONT&& cont, LIST&& list ) :
  Base( std::move( base) ),
  cont( std::move( cont ) ),
  list( std::move( list ) ){
  try {
  } catch( std::exception& e ){
    Log::info( "Encountered error while parsing ENDF BreitWigner subsection" );
    throw e;
  }
}

template< typename Iterator >
BreitWigner( Base&& base, TAB1&& tab1, CONT&& cont,
                       Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
    BreitWigner( std::forward<Base>(base), 
                 std::forward<TAB1>(tab1),
                 std::forward<CONT>(cont),
                 LIST( it, end, lineNumber, MAT, MF, MT ) ){ }

template< typename Iterator >
BreitWigner( Base&& base, CONT&& cont,
                       Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
    BreitWigner( std::forward<Base>(base), std::forward<CONT>(cont),
                            LIST( it, end, lineNumber, MAT, MF, MT ) ){ }

template< typename Iterator >
BreitWigner( Base&& base, TAB1&& tab1,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
  try:
    BreitWigner( std::forward<Base>(base), std::forward<TAB1>(tab1),
                 CONT( it, end, lineNumber, MAT, MF, MT ),
                 it, end, lineNumber, MAT, MF, MT )
{
} catch ( std::exception& e ){
  Log::info( "Encountered error while parsing ENDF BreitWigner subsection" );
  throw e;
} catch ( int nPosition ){
  Log::info( "Error in position {}", nPosition );
  Log::info( "Error encountered while parsing CONT record" );
  throw std::exception();
}

template< typename Iterator >
BreitWigner( Base&& base, 
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try:
    BreitWigner( std::forward<Base>(base),
                            CONT( it, end, lineNumber, MAT, MF, MT ),
                            it, end, lineNumber, MAT, MF, MT )
{
} catch ( std::exception& e ){
  Log::info( "Encountered error while parsing ENDF BreitWigner subsection" );
  throw e;
} catch ( int nPosition ){
  Log::info( "Error in position {}", nPosition );
  Log::info( "Error encountered while parsing CONT record" );
  throw std::exception();
}