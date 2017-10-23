template< typename Iterator >
EnergyDependent ( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT ) : 
  interpolation_( begin, end, lineNumber, MAT, MF, MT  ),
  lists_( readLists( begin, end, lineNumber, MAT, MF, MT,
  interpolation_.NZ() ) ) {}

