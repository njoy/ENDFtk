/**
 *  @brief Parse the file
 *
 *  @param[in] lineNumber   the line number to be used in parsing
 */
template< int MF >
file::Type< MF > parse( long& lineNumber ) const {

  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  StructureDivision division( position, end, lineNumber );
  return { division, position, end, lineNumber };
}

/**
 *  @brief Parse the file
 */
template< int MF >
file::Type< MF > parse() const {

  long lineNumber = 1;
  return this->parse<MF>( lineNumber );
}

/**
 *  @brief Parse the file
 */
template< long long MF, typename... Args >
auto parse( hana::llong<MF>, Args&... args ) const {
  return this->parse<MF>( args... );
}
