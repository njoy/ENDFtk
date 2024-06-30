/**
 *  @brief Return iterator to the file with the given mf number
 *
 *  @param[in] mf    the mf number
 */
auto find( int mf ) {

  auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                [] ( auto&& left, auto&& right )
                                   { return left.fileNumber() < right; } );

  if ( iter != this->files_.end() ) {

    if ( iter->fileNumber() == mf ) {

      return iter;
    }
  }
  return this->files_.end();
}

/**
 *  @brief Return iterator to the file with the given mf number
 *
 *  @param[in] mf    the mf number
 */
auto find( int mf ) const {

  auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                [] ( auto&& left, auto&& right )
                                   { return left.fileNumber() < right; } );

  if ( iter != this->files_.end() ) {

    if ( iter->fileNumber() == mf ) {

      return iter;
    }
  }
  return this->files_.end();
}
