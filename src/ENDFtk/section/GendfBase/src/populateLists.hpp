template< typename BufferIterator >
static auto populateLists(HeadRecord& head,
                          BufferIterator& begin,
                          const BufferIterator& end,
                          long& lineNumber,
                          int MAT ) {

  // initialize
  std::vector< ListRecord > list_records;

  // first list record
  list_records.emplace_back(
    ListRecord(begin, end, lineNumber, MAT, head.MF(), head.MT()) );

  // loop until SEND is found

  Log::info( "Previous: {}, Head: {}", list_records.back().N2(), head.N2() );

  while( list_records.back().N2() < head.N2() ) {

    // emplace next record
    list_records.emplace_back(
      ListRecord(begin, end, lineNumber, MAT, head.MF(), head.MT()) );

    Log::info( "Previous: {}, Head: {}", list_records.back().N2(), head.N2() );

  }

  // read SEND card
  readSEND(begin, end, lineNumber, MAT, head.MF());

  return list_records;

}
