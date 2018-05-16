NBodyPhaseSpace( double APSX, long NPSX ) :
  ControlRecord( APSX, 0.0, 0, 0, 0, NPSX ) {};

template< typename Iterator >
NBodyPhaseSpace( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT ) :
  ControlRecord( begin, end, lineNumber, MAT, MF, MT  ) {}

