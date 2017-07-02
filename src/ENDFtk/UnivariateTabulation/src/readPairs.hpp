template< typename Iterator >
static std::tuple< std::vector< double >, std::vector< double > >
readPairs
( long nPairs, Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT ){
  std::tuple< std::vector< double >, std::vector< double > > result;
  try{
    if ( nPairs < 1 ){
      Log::error( "Encountered invalid NP value while constructing TAB1 record" );
      Log::info( "NP is required to be greater than zero" );
      throw std::exception();
    }
    
    result = record::Zipper::unzip
             < record::Real, record::Real >
             ( nPairs, it, end, lineNumber, MAT, MF, MT );
    auto& xValues = std::get< 0 >( result );
    verifyXValuesAreSorted( xValues );
    return result;
  } catch ( std::exception& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
    throw e; 
  }
}
