template< typename Iterator >
static std::vector< Subsection >
readSubsections( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT,
                 int size ) {

  std::vector< Subsection > sections;
  sections.reserve( size );

  while( size-- ) {

    sections.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return sections;
}
