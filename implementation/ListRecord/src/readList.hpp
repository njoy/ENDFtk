template< typename Iterator >
static std::vector< double >
readList( long nEntries, Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ){
  std::vector< double > list;
  if ( nEntries < 0 ){
    LOG(ERROR) << "List specified with negative number of entries";
    LOG(INFO)  << "nEntries: " << nEntries;
    throw std::exception();
  }
  list.resize( nEntries );
  auto listIt = list.begin();
  auto nLines = nEntries / 6;
  while ( nLines-- ){
    ListLine::read( it, end,
                    listIt[0], listIt[1], listIt[2],
                    listIt[3], listIt[4], listIt[5] );
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    listIt += 6;
    ++lineNumber;
  }
  auto nPartial = nEntries % 6;
  std::array< double, 5 > sink;
  switch ( nPartial ){
  case 0: break;
  case 1: {
    ListLine::read( it, end,
                    listIt[0], sink[4], sink[3], sink[2], sink[1], sink[0] );
    break;
  }
  case 2: {
    ListLine::read( it, end,
                    listIt[0], listIt[1], sink[3], sink[2], sink[1], sink[0] );
    break;
  }
  case 3: {
    ListLine::read( it, end,
                    listIt[0], listIt[1], listIt[2],
                    sink[2], sink[1], sink[0] );
    break;
  }
  case 4: {
    ListLine::read( it, end,
                    listIt[0], listIt[1], listIt[2],
                    listIt[3], sink[1], sink[0] );
    break;
  }
  case 5: {
    ListLine::read( it, end,
                    listIt[0], listIt[1], listIt[2],
                    listIt[3], listIt[4], sink[0] );
    break;
  }
  default: {
    throw std::exception();
  }
  }
  if (nPartial){
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    ++lineNumber;
  }
  int requiredChecks = ( 6 - nPartial );
  auto sinkIt = sink.begin();
  while ( requiredChecks-- ){
    if ( *sinkIt++ != 0.0 ){
      LOG(ERROR) <<
        "Nonzero entry encountered in List record where none was expected";
      auto begin = it;
      while ( *begin != '\n' ){ --begin; }
      ++begin;
      throw std::runtime_error("Too many entries in List record");
    }
  }
  return list;
}
