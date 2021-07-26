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

/**
 *  @brief Parse the section
 */
template< long long MF, long long... OptionalMT>
auto parse( hana::llong<MF>, hana::llong<OptionalMT>... ) const {

  return parse< MF, OptionalMT... >();
}

/**
 *  @brief Parse the section
 */
template< long long MF>
auto parse( hana::llong<MF>, long& lineNumber ) const {

  return parse< MF >( lineNumber );
}

/**
 *  @brief Parse the section
 */
template< long long MF, long long MT>
auto parse( hana::llong<MF>, hana::llong<MT>, long& lineNumber ) const {

  return parse< MF, MT >( lineNumber );
}
