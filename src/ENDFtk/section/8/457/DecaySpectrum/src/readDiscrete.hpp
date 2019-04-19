template< typename Iterator >
static std::vector< DiscreteSpectrum >
readDiscrete( Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT,
              int size ) {
  
  std::vector< DiscreteSpectrum > sequence;
  sequence.reserve( size );

  while( size-- ){
    sequence.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return sequence;
}
