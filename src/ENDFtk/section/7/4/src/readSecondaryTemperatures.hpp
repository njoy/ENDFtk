template< typename Iterator, typename Array >
static std::vector< std::optional< EffectiveTemperature > >
readSecondaryTemperatures( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT,
                           const Array& types ) {
  unsigned int size = types.size();
  std::vector< std::optional< EffectiveTemperature > > sequence;
  sequence.reserve( size );

  while( size-- ){
    if ( types[ sequence.size() ] != 0. ) {
      sequence.push_back( EffectiveTemperature( begin, end, lineNumber,
                                                MAT, MF, MT ) );
    }
    else {
      sequence.push_back( std::nullopt );
    }
  }

  return sequence;
}
