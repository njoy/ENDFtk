/**
 *  @brief Remove all materials with the given MAT number
 *
 *  @param[in]   mat   the mat number of the materials to be removed
 */
void remove( int mat ) {

  this->materials_.erase( mat );
}
