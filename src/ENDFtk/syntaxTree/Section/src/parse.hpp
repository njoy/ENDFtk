template< int MF >
section::Type< MF > parse( long& lineNumber, int MAT ){
  auto begin = this->bufferBegin();
  auto end = this->bufferEnd();

  return section::Type< MF >( this->head, begin, end, lineNumber, MAT );
}
