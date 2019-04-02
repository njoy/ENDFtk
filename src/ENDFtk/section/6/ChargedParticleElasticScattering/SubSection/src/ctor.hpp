SubSection( SubSectionVariant&& subsection ) :
  data_( subsection ) {}

SubSection( NuclearAmplitudeExpansion&& subsection ) :
  data_( subsection ) {}

SubSection( LegendreCoefficients&& subsection ) :
  data_( subsection ) {}

SubSection( NuclearPlusInterference&& subsection ) :
  data_( subsection ) {}

template< typename Iterator >
SubSection ( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int MF,
             int MT ) :
  SubSection( readSubSection( begin, end, lineNumber, MAT, MF, MT ) ) {}

