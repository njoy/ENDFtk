/**
 *  @brief Clean up the file
 *
 *  This function removes the sequence numbers from the file
 */
void clean() {

  for ( auto& section : this->sections() ) {

    section.clean();
  }
}
