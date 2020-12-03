/**
 *  @brief Parse the material
 *
 *  @param[in] lineNumber   the line number to be used in parsing
 */
::njoy::ENDFtk::Material parse( long& lineNumber ) const {

  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  StructureDivision division( position, end, lineNumber );
  return { division, position, end, lineNumber };
}

/**
 *  @brief Parse the material
 */
::njoy::ENDFtk::Material parse() const {

  long lineNumber = 1;
  return this->parse( lineNumber );
}
