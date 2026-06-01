template<typename Iterator>
static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) {

  std::vector< DataRecord > records;
  int ngn;

  ControlRecord cont( it, end, lineNumber, MAT, MF, MT );
  ngn = cont.N2();

  do {

    records.emplace_back(it, end, lineNumber, MAT, MF, MT);
  }
  while ( records.back().IG() < ngn );

  return std::make_tuple( ngn, records );
}
