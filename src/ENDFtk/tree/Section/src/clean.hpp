/**
 *  @brief Clean up the section
 *
 *  This section removes the sequence numbers from the section
 */
void clean() {

  int NC = this->NC();
  std::string content = this->content();
  auto position = content.begin();
  auto end = content.end();
  long lineNumber = 0;

  this->content_.clear();
  auto output = std::back_inserter( this->content_ );

  while ( NC-- > 0 ) {

    TextRecord text( position, end, lineNumber, this->MAT(), this->MF(), this->MT() );
    text.print( output, this->MAT(), this->MF(), this->MT() );
  }
  SEND( this->MAT(), this->MF() ).print( output );
}
