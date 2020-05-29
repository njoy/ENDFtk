template< typename Iterator >
static std::vector< JValue >
readJValues( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT,
             int size ) {

  std::vector< JValue > jvalues;
  jvalues.reserve( size );

  while( size-- ) {

    jvalues.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return jvalues;
}
