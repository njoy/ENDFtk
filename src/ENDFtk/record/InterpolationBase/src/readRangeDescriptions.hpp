template< typename Iterator >
static std::tuple< std::vector< long >, std::vector< long > >
readRangeDescriptions
( long nRanges, Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT ){
  try{
    std::tuple< std::vector< long >, std::vector< long > > result;
    result = record::Zipper::unzip< record::Integer<11>, record::Integer<11> >
             ( nRanges, it, end, lineNumber, MAT, MF, MT );
    auto& boundaryIndices = std::get< 0 >( result );
    verifyBoundaryIndicesAreSorted( boundaryIndices );
    return result;
  } catch( std::exception& e ){
    Log::info( "Error encountered reading range descriptions" );
    throw e;
  }
}
