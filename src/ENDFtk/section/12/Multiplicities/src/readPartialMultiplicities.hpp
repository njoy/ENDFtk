template< typename Iterator >
static std::vector< PartialMultiplicity >
readPartialMultiplicities( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT,
                           int size ) {

  std::vector< PartialMultiplicity > partials;
  partials.reserve( size );

  while( size-- ) {

    partials.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return partials;
}
