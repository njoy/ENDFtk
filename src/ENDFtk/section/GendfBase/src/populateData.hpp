template< typename BufferIterator >
auto populateData(HeadRecord& head,
                  BufferIterator& begin,
                  const BufferIterator& end,
                  long& lineNumber,
                  int MAT ) {

  // initialize
  std::map< int, GendfDataRecord > data_records;

  // first list record
  auto next_record = GendfDataRecord( begin, end, lineNumber,
                                      num_legendre_, num_sigma0_,
                                      MAT, head.MF(), head.MT() );
  int group = next_record.group();
  data_records.emplace( group, next_record );

  // loop until final group is recorded
  while( group < head.N2() ) {

    // create next record
    next_record = GendfDataRecord( begin, end, lineNumber,
                                   num_legendre_, num_sigma0_,
                                   MAT, head.MF(), head.MT() );
    group = next_record.group();

    // check if group was already seen
    if (data_records.count( group ) > 0) {
      Log::info( "Group {} appears multiple times in MFD/MT {}/{}",
                 group, head.MF(), head.MT() );
      throw std::exception();
    }

    data_records.emplace( group, next_record );

  }

  // read SEND card
  readSEND(begin, end, lineNumber, MAT, head.MF());

  return data_records;

}
