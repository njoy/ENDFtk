template < typename Range >
static std::vector< double >
extractReal( const Range& values ) {

  std::vector< double > real;
  for ( const auto& value : values ) {

    real.push_back( value.real() );
  }
  return real;
}

template < typename Range >
static std::vector< double >
extractImaginary( const Range& values ) {

  std::vector< double > real;
  for ( const auto& value : values ) {

    real.push_back( value.imag() );
  }
  return real;
}
