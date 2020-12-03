/**
 *  @brief Function to read a sequence of ENDF components
 *
 *  @tparam Component        an ENDF component
 *  @tparam Iterator         an input iterator
 *
 *  This function requires the ENDF component to have a read style
 *  constructor.
 */
template< typename Iterator >
std::vector< Material >
readMaterials( Iterator& begin,
               const Iterator& end,
               long& lineNumber ) {

  std::vector< Material > sequence;

  StructureDivision division( begin, end, lineNumber );
  while ( division.tail.MAT() != -1 ) {

    sequence.emplace_back( division, begin, end, lineNumber );
    division = StructureDivision( begin, end, lineNumber );
  }

  return sequence;
}
