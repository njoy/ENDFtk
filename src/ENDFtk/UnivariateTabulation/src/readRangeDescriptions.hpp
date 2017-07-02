template< typename Iterator >
static std::tuple< std::vector< long >, std::vector< long > >
readRangeDescriptions
( long nRanges, Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT ){
  std::tuple< std::vector< long >, std::vector< long > > result;
  try{
    if ( nRanges < 1 ){
      Log::error( "Encountered invalid NR value while constructing TAB1 record" );
      Log::info( "NR is required to be greater than zero" );
      throw std::exception();
    }
    
    result = record::Zipper::unzip
             < record::Integer<11>,
	       record::Integer<11> >
             ( nRanges, it, end, lineNumber, MAT, MF, MT );
    auto& boundaryIndices = std::get< 0 >( result );
    verifyBoundaryIndicesAreSorted( boundaryIndices );
    return result;
  } catch ( std::exception& e ){
    Log::info( "Error while reading TAB1 range information" );
    throw e; 
  }
}
