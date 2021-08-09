/**
 *  @brief Remove the file in the material if it is present
 *
 *  @param[in]   mf   the mf number of the file to be removed
 */
void remove( int mf ) {

  auto iter = this->files_.find( mf );
  if ( iter != this->files_.end() ) {

    this->files_.erase( iter );
  }
}

/**
 *  @brief Remove the section in the material if it is present
 *
 *  @param[in]   mf   the mf number of the section to be removed
 *  @param[in]   mt   the mt number of the section to be removed
 */
void remove( int mf, int mt ) {

  auto iter = this->files_.find( mf );
  if ( iter != this->files_.end() ) {

    iter->second.remove( mt );
  }
}
