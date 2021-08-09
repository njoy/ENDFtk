/**
 *  @brief Parse the tape
 *
 *  @param[in] lineNumber   the line number to be used in parsing
 */
::njoy::ENDFtk::Tape parse( long& lineNumber ) const {

  std::string content = this->content();
  auto position = content.begin();
  auto end = content.end();

  return { position, end, lineNumber };
}

/**
 *  @brief Parse the tape
 */
::njoy::ENDFtk::Tape parse() const {

  long lineNumber = 1;
  return this->parse( lineNumber );
}
