template< typename Iterator >
static std::optional< std::vector< DiscreteSpectrum > >
readDiscrete( Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT,
              int lcon,
              int size ) {
  if ( lcon == 1 ) return std::nullopt;
  
  std::vector< DiscreteSpectrum > sequence;
  sequence.reserve( size );

  while( size-- ){
    sequence.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return std::make_optional( std::move( sequence ) );
}
