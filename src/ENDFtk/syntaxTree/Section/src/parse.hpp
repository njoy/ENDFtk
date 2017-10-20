template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse( long& lineNumber ){
  auto position = this->buffer().begin();
  auto end = this->buffer().end();

  HeadRecord head( position, end, lineNumber );
  return section::Type< MF, OptionalMT... >
         ( head, position, end, lineNumber, head.MAT() );
}

template< int MF, int... OptionalMT >
section::Type< MF, OptionalMT... > parse(){
  long lineNumber = 1;
  return parse< MF, OptionalMT... >( lineNumber );
}
