template< typename Iterator >
static ReichMooreScatteringRadiusUncertainties
read( Iterator& begin, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ) {

  return ReichMooreScatteringRadiusUncertainties( begin, end, lineNumber,
                                                  MAT, MF, MT );
}
