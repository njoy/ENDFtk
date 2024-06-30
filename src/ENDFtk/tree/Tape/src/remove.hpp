/**
 *  @brief Remove all materials with the given MAT number
 *
 *  @param[in]   mat   the mat number of the materials to be removed
 */
void remove( int mat ) {

  auto range = this->find( mat );
  this->materials_.erase( range.first, range.second );
}
