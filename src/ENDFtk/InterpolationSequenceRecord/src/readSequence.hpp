template< typename Iterator >
static std::vector< Record >
readSequence( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT,
                      int size ) {
  std::vector< Record > sequence;
  sequence.reserve( size );

  while( size-- ){
    sequence.emplace_back( begin, end, lineNumber, MAT, MF, MT );
    validateElement( sequence.back() );
  }
  
  validateSequence( sequence );

  return sequence;
}
