template< int MF >
section::Type< MF > parse( long& lineNumber, int MAT ){
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  HeadRecord head( position, end, lineNumber );
  return section::Type< MF >( head, position, end, lineNumber, MAT );
}
