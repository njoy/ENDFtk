template< typename Iterator >
SubSection ( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT ) :
  SubSectionVariant( readSubSection( begin, end, lineNumber, MAT, MF, MT ) ) {}

