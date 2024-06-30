/**
 *  @brief Return iterator to the file with the given mf number
 *
 *  @param[in] mt    the mf number
 */
auto find( int mf ) {

  auto getMF = [] ( auto&& value ) { return value.MF(); };
  auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                [&getMF] ( auto&& left, auto&& right )
                                         { return std::visit( getMF, left ) < right; } );

  if ( iter != this->files_.end() ) {

    if ( std::visit( getMF, *iter ) == mf ) {

      return iter;
    }
  }
  return this->files_.end();
}

/**
 *  @brief Return iterator to the section with the given mf number
 *
 *  @param[in] mf    the mf number
 */
auto find( int mf ) const {

  auto getMF = [] ( auto&& value ) { return value.MF(); };
  auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                [&getMF] ( auto&& left, auto&& right )
                                         { return std::visit( getMF, left ) < right; } );

  if ( iter != this->files_.end() ) {

    if ( std::visit( getMF, *iter ) == mf ) {

      return iter;
    }
  }
  return this->files_.end();
}
