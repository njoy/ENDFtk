/**
 *  @brief Return iterator to the file with the given mat number
 *
 *  @param[in] mat    the mat number
 */
auto find( int mat ) {

  auto lower = std::lower_bound( this->materials_.begin(), this->materials_.end(), mat,
                                 [] ( auto&& left, auto&& right )
                                    { return left.materialNumber() < right; } );
  auto upper = std::upper_bound( this->materials_.begin(), this->materials_.end(), mat,
                                 [] ( auto&& left, auto&& right )
                                    { return left < right.materialNumber(); } );

  if ( lower != upper ) {

    return std::make_pair( lower, upper );
  }
  return std::make_pair( this->materials_.end(), this->materials_.end() );
}

/**
 *  @brief Return iterator to the file with the given mat number
 *
 *  @param[in] mat    the mat number
 */
auto find( int mat ) const {

  auto lower = std::lower_bound( this->materials_.begin(), this->materials_.end(), mat,
                                 [] ( auto&& left, auto&& right )
                                    { return left.materialNumber() < right; } );
  auto upper = std::upper_bound( this->materials_.begin(), this->materials_.end(), mat,
                                 [] ( auto&& left, auto&& right )
                                    { return left < right.materialNumber(); } );

  if ( lower != upper ) {

    return std::make_pair( lower, upper );
  }
  return std::make_pair( this->materials_.end(), this->materials_.end() );
}
