/**
 *  @brief Function to read a sequence of ENDF components
 *
 *  @tparam Component        an ENDF component
 *  @tparam Iterator         an input iterator
 *
 *  This function requires the ENDF component to have a read style constructor.
 */
template< typename Component, typename Iterator >
std::vector< Component >
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
