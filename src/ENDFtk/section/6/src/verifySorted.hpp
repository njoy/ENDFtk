template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true,
          typename String >
static void
verifySorted( const Range& values, const String& name ){

  auto iter = std::is_sorted_until( values.begin(), values.end() );
  const bool valuesAreSorted = ( iter == values.end() );

  if ( not valuesAreSorted ){

    Log::error( "{} values are not sorted", name );
    const auto position = iter - values.begin();
    Log::info( "{} value [{}]: {}", name, (position - 1), iter[-1] );
    Log::info( "{} value [{}]: {}", name, position, iter[0] );
    throw std::exception();
  }
}

