template< typename Iterator >
static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int NGN ) {

  std::vector< DataRecord > records;

  // need to find max nonzero gamma group index
  int max_gg = 0;
  do {

    records.emplace_back(it, end, lineNumber, MAT, MF, MT);
    if ( max_gg < ( (records.back().NG2() - 1 ) + records.back().IG2LO() ) ) {

      max_gg = (records.back().NG2() - 1 ) + records.back().IG2LO();
    }
  }
  while ( records.back().IG() < NGN);

  return std::make_tuple( records, max_gg );
}