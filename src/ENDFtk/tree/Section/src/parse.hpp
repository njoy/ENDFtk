/**
 *  @brief Parse the section
 *
 *  @param[in] lineNumber   the line number to be used in parsing
 */
template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse( long& lineNumber ) const {

  auto position = this->content().begin();
  auto end = this->content().end();

  HeadRecord head( position, end, lineNumber );
  return { head, position, end, lineNumber, head.MAT() };
}

/**
 *  @brief Parse the section
 */
template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse() const {

  long lineNumber = 1;
  return this->parse< MF, OptionalMT... >( lineNumber );
}
