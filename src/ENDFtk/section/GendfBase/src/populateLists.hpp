template< typename BufferIterator >
static auto populateLists(HeadRecord& head,
                          BufferIterator& begin,
                          const BufferIterator& end,
                          long& lineNumber,
                          int MAT ) {

  // initialize
  std::map< int, ListRecord > list_records;

  // first list record
  auto next_record = ListRecord( begin, end, lineNumber,
                                 MAT, head.MF(), head.MT() );
  int group = next_record.N2();
  list_records.emplace( group, next_record );

  // loop until final group is recorded
  while( group < head.N2() ) {

    // create next record
    next_record = ListRecord( begin, end, lineNumber,
                              MAT, head.MF(), head.MT() );
    group = next_record.N2();

    // check if group was already seen
    if (list_records.count( group ) > 0) {
      Log::info( "Group {} appears multiple times in MFD/MT {}/{}",
                 group, head.MF(), head.MT() );
      throw std::exception();
    }

    list_records.emplace( group, next_record );

  }

  // read SEND card
  readSEND(begin, end, lineNumber, MAT, head.MF());

  return list_records;

}
