template< typename Iterator >
static std::vector< SpinGroup >
readSpinGroups( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT,
                int size ) {

  std::vector< SpinGroup > groups;
  groups.reserve( size );

  while( size-- ) {

    groups.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return groups;
}
