template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse( long& lineNumber ) const {
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  HeadRecord head( position, end, lineNumber );
  return { head, position, end, lineNumber, head.MAT() };
}

template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse() const {
  long lineNumber = 1;
  return this->parse< MF, OptionalMT... >( lineNumber );
}

template< long long MF, long long... OptionalMT>
auto parse( hana::llong<MF>, hana::llong<OptionalMT>... ) const {

  return parse< MF, OptionalMT... >();
}

template< long long MF>
auto parse( hana::llong<MF>, long& lineNumber ) const {

  return parse< MF >( lineNumber );
}

template< long long MF, long long MT>
auto parse( hana::llong<MF>, hana::llong<MT>, long& lineNumber ) const {

  return parse< MF, MT >( lineNumber );
}
