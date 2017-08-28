template< int MF >
file::Type< MF > parse( long& lineNumber ){
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  StructureDivision division( position, end, lineNumber );
  return file::Type< MF >( division, position, end, lineNumber );
}
