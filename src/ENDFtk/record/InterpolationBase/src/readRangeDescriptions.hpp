template< typename Iterator >
static std::tuple< std::vector< long >, std::vector< long > >
readRangeDescriptions
( long nRanges, Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT ){
  std::tuple< std::vector< long >, std::vector< long > > result;
  result = record::Zipper::unzip< record::Integer<11>, record::Integer<11> >
           ( nRanges, it, end, lineNumber, MAT, MF, MT );
  auto& boundaryIndices = std::get< 0 >( result );
  verifyBoundaryIndicesAreSorted( boundaryIndices );
  return result;
}
