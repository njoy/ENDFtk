template < typename Range >
static std::vector< double >
extractReal( const Range& values ) {

  using namespace njoy::tools;
  auto reals = values | std20::views::transform(
                          [] ( const auto& complex )
                             { return complex.real(); } );
  return { reals.begin(), reals.end() };
}

template < typename Range >
static std::vector< double >
extractImaginary( const Range& values ) {

  using namespace njoy::tools;
  auto imags = values | std20::views::transform(
                          [] ( const auto& complex )
                             { return complex.imag(); } );
  return { imags.begin(), imags.end() };
}
