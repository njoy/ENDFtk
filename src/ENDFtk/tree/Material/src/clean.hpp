/**
 *  @brief Clean up the material
 *
 *  This function removes the sequence numbers from the material
 */
void clean() {

  for ( auto& file : this->files() ) {

    file.clean();
  }
}
