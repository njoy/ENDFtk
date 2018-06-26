static std::vector< ListRecord >
generateTemperatures( double beta,
                      std::vector< double >&& temperatures,
                      std::vector< long >&& li,
                      std::vector< std::vector< double > >&& s ) {
  unsigned int size = temperatures.size() - 1;
  std::vector< ListRecord > sequence;
  sequence.reserve( size );

  unsigned int i = 0;
  while( i++ < size ){
    sequence.emplace_back( ListRecord( temperatures[i], beta, li[i-1], 0, 0,
                                       std::move( s[i] ) ) );
  }

  return sequence;
}
