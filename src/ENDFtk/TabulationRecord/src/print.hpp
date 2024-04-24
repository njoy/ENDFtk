/**
 *  @brief Print the record
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 *  @param[in] MT            the MT number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  record::InterpolationBase::print( it, MAT, MF, MT );

  using namespace njoy::tools;

  using Format = disco::Record< disco::ENDF, disco::ENDF,
                                disco::ENDF, disco::ENDF,
                                disco::ENDF, disco::ENDF,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::Column< 5 > >;

  auto nFullLines = this->NP() / 3;
  auto partialLineEntries = this->NP() - nFullLines * 3;

  auto x = this->x().begin();
  auto y = this->y().begin();

  while ( nFullLines-- ){
    Format::write( it, x[0], y[0], x[1], y[1], x[2], y[2], MAT, MF, MT );
    x += 3; y += 3;
  }

  if ( partialLineEntries ){
    auto blankEntries = 2 * ( 3 - partialLineEntries );
    while ( partialLineEntries-- ){
      disco::ENDF::write( *x, it );
      disco::ENDF::write( *y, it );
      ++x; ++y;
    }

    while ( blankEntries-- ){ disco::Column< 11 >::write( it ); }

    using Format =
      disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                     disco::Integer< 3 >, disco::Column< 5 > >;

    Format::write( it, MAT, MF, MT );
  }
}
