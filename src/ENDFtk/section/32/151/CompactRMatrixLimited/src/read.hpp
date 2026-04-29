template< typename Iterator >
static ReichMooreScatteringRadiusUncertainties
read( Iterator&, const Iterator&, long&,
      int, int, int ) {

  // return ReichMooreScatteringRadiusUncertainties( begin, end, lineNumber,
  //                                                 MAT, MF, MT );

  Log::error( "Scattering radius uncertainties in the R-matrix limited representation "
              "are not supported yet." );
  throw std::exception();
}
