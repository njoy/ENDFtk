/**
 *  @brief Clean up the tape
 *
 *  This function removes the sequence numbers from the tape
 */
void clean() {

  for ( auto& material : this->materials() ) {

    material.clean();
  }
}
