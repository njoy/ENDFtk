template< typename Iterator >
static std::vector< int > readIntegers( Iterator& it, const Iterator& end ) {

  std::vector< int > sequence;

  // NDIGIT != 6 : there's a space
  if ( NDIGIT != 6 ) { ++it; }

  // read N ints of length NDIGIT + 1
  for ( unsigned int i = 0; i < N; ++i ) {

    sequence.emplace_back( record::Integer< NDIGIT + 1 >::Parser::read( it, end ) );
  }

  // remove trailing zeros
  auto iter = std::find_if( sequence.rbegin(), sequence.rend(),
                            [] ( auto value ) { return value != 0; } ).base();
  sequence.erase( iter, sequence.end() );

  // NDIGIT == 2 and 5 : there's a space, NDIGIT == 3: there's three spaces
  switch ( NDIGIT ) {

    case 2 :
    case 5 : { it += 1; break; }
    case 3 : { it += 3; break; }
    default : { break; }
  }

  return sequence;
}
