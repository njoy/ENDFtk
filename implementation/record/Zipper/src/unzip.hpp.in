template< typename... ENDFTypes, typename Iterator >
static std::tuple< std::vector< typename ENDFTypes::Type >... >
unzip
( uint64_t nEntries,
  Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT ){
    
  std::tuple< std::vector< typename ENDFTypes::Type >... > result;    
  reserve( nEntries, result );

  using Zip = Zipped< ENDFTypes... >;
  auto iterators = makeIteratorTuple( result, Zip::tupleIndices );

  int remainingLines = nEntries / Zip::tuplesPerRecord;
  while ( remainingLines-- ){
    readLine< Zip >( iterators, it, end, lineNumber, MAT, MF, MT );
    increment< Zip >( iterators );
  }
    
  const int remainingEntries = nEntries % Zip::tuplesPerRecord;
  if ( remainingEntries ){
    readPartialLine< Zip >
      ( remainingEntries, iterators, it, end, lineNumber,
        MAT, MF, MT, Zip::tupleIndices );
  }
    
  return result;
}
