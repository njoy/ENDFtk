template< typename Iterator >
static std::vector< LValue >
readLValues( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT,
             int size ) {

  std::vector< LValue > lvalues;
  lvalues.reserve( size );

  while( size-- ) {

    lvalues.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return lvalues;
}
