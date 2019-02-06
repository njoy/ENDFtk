SubSection( SubSectionVariant&& subsection ) :
  data_( subsection ) {}

SubSection( LegendreCoefficients&& subsection ) :
  data_( subsection ) {}

SubSection( Tabulated&& subsection ) :
  data_( subsection ) {}

template< typename Iterator >
SubSection ( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT ) :
  data_( readSubSection( begin, end, lineNumber, MAT, MF, MT ) ) {}

