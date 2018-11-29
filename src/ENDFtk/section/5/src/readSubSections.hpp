template< typename Iterator >
static std::vector< SubSection >
readReactionProducts( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT,
                      int size ) {
  std::vector< SubSection > sections;
  sections.reserve( size );

  while( size-- ){
    sections( begin, end, lineNumber, MAT, MF, MT );
  }

  return sections;
}
