template< typename Iterator >
static ReichMooreScatteringRadiusUncertainties
read( Iterator& begin, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ) {

  // return ReichMooreScatteringRadiusUncertainties( begin, end, lineNumber,
  //                                                 MAT, MF, MT );

  Log::error( "Scattering radius uncertainties in the R-matrix limited representation "
              "are not supported yet." );
  throw std::exception();
}
