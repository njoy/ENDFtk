template< typename Iterator >
static std::vector< PartialCrossSection >
readPartialMultiplicities( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT,
                           int size ) {

  std::vector< PartialCrossSection > partials;
  partials.reserve( size );

  while( size-- ) {

    partials.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return partials;
}
