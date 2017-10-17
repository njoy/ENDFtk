template< typename Iterator >
Subsection( Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MT )
  try:
    TabulationRecord( begin, end, lineNumber, MAT, 13, MT ){
  } catch( std::exception& e ){
    Log::info( "Encountered error while reading MF=13 Subsection." );
    throw e;
  }

Subsection( TabulationRecord&& tab1 ) :
  TabulationRecord( std::move(tab1) ){}
