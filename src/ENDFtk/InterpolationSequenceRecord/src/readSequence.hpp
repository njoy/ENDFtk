template< typename Iterator >
static std::vector< Component >
readSequence( Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT,
              int size ) {

  std::vector< Component > sequence;
  sequence.reserve( size );

  while ( size-- ) {

    sequence.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return sequence;
}
