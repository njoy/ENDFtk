
SingleLevelBreitWigner( Base&& base, CONT&& cont, LIST&& list ) :
  Base(base),
  cont( std::move( cont ) ),
  list( std::move( list ) ){
  try {
  } catch( std::exception& e ){
  }
}

template< typename Iterator >
SingleLevelBreitWigner( Base&& base, CONT&& cont,
                       Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
    SingleLevelBreitWigner( std::forward<Base>(base), std::forward<CONT>(cont),
                            LIST( it, end, lineNumber, MAT, MF, MT ) ){ }

template< typename Iterator >
SingleLevelBreitWigner( Base&& base, 
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
  try:
    SingleLevelBreitWigner( std::forward<Base>(base),
                            CONT( it, end, lineNumber, MAT, MF, MT ),
                            it, end, lineNumber, MAT, MF, MT )
{
} catch ( std::exception& e ){
  Log::info( "Encountered error while parsing ENDF SLBW subsection" );
  throw e;
} catch ( int nPosition ){
  Log::info( "Error in position {}", nPosition );
  Log::info( "Error encountered while parsing CONT record" );
  throw std::exception();
}


