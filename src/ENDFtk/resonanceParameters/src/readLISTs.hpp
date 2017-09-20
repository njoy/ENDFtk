template< typename Iterator >
static std::vector< LIST >
readLISTs( int NLS,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  return read<LIST>( NLS, it, end, lineNumber, MAT, MF, MT );
}

template< typename Iterator >
static std::vector< LIST >
readLISTs( const ControlRecord& cont,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){
  return readLISTs( cont.N1(), it, end, lineNumber, MAT, MF, MT );
}
