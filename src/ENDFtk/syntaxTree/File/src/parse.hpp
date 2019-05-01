template< int MF >
file::Type< MF > parse( long& lineNumber ) const {
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  StructureDivision division( position, end, lineNumber );
  return { division, position, end, lineNumber };
}

template< int MF >
file::Type< MF > parse() const {
  long lineNumber = 1;
  return this->parse<MF>( lineNumber );
}

template< long long MF, typename... Args >
auto parse( hana::llong<MF>, Args&... args ) const { 
  return this->parse<MF>( args... );
}
