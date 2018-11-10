template< typename Iterator >
static std::vector< DecaySpectrum >
readSpectra( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int size ) {
  std::vector< DecaySpectrum > sequence;
  sequence.reserve( size );

  while( size-- ){
    sequence.emplace_back( begin, end, lineNumber, MAT, 8, 457 );
  }

  return sequence;
}
