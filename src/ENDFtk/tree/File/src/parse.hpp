/**
 *  @brief Parse the file
 *
 *  @param[in] lineNumber   the line number to be used in parsing
 */
template< int MF >
file::Type< MF > parse( long& lineNumber ) const {

  std::string content = this->content();
  auto position = content.begin();
  auto end = content.end();

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
