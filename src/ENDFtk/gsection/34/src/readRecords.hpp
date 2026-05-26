template<typename Iterator>
static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) {

  std::vector< DataRecord > records;
  int ngn;
  int l;
  int l1;

  ControlRecord cont( it, end, lineNumber, MAT, MF, MT );
  ngn = cont.N2();
  l = cont.L2();
  l1 = cont.N1();

  do {

    records.emplace_back(it, end, lineNumber, MAT, MF, MT);
  }
  while ( records.back().IG() < ngn );

  return std::make_tuple( l, l1, ngn, records );
}
