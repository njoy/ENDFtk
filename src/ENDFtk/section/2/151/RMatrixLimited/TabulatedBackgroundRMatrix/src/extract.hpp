template < typename Range >
static std::vector< double >
extractReal( const Range& values ) {

  return ranges::to< std::vector< double > >(
             values | ranges::views::transform( [] ( const auto& complex )
                                                   { return complex.real(); } ) );
}

template < typename Range >
static std::vector< double >
extractImaginary( const Range& values ) {

  return ranges::to< std::vector< double > >(
             values | ranges::views::transform( [] ( const auto& complex )
                                                   { return complex.imag(); } ) );
}
