SubSection( SubSectionVariant&& subsection ) :
  SubSectionVariant( subsection ) {}

template< typename Iterator >
SubSection ( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT ) :
  SubSection( readSubSection( begin, end, lineNumber, MAT, MF, MT ) ) {}

