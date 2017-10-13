template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse( long& lineNumber, int MAT ){
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  HeadRecord head( position, end, lineNumber );
  return section::Type< MF, OptionalMT... >( head, position, end, lineNumber, MAT );
}
