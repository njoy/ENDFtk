template< typename Iterator >
static ScatteringLaw
readScatteringLaw( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT,
                   double B1 ) {

  if ( B1 == 0.0 ) {

    return AnalyticalFunctions();
  }
  else {
    
    return TabulatedFunctions( begin, end, lineNumber, MAT, MF, MT );
  }
}
