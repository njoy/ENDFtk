/**
 *  @brief Remove the section in the file if it is present
 *
 *  @param[in]   mt   the mt number of the section to be removed
 */
void remove( int mt ) {

  auto iter = this->find( mt );
  if ( iter != this->sections_.end() ) {

    this->sections_.erase( iter );
  }
}
