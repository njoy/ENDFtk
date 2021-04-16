template< typename Iterator >
static auto readRecords(
  Iterator& it, const Iterator& end, long MAT,
  long MF, long MT, unsigned int NGN ) {

  std::map< unsigned int, DataRecord > result;

  do {

    long lineNumber = 0;
    auto record = DataRecord( it, end, lineNumber, MAT, MF, MT );
    result.emplace( record.IG(), record );

  } while( result.rbegin()->first < NGN );

  return result;
}
