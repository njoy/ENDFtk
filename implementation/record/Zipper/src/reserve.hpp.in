template< typename Tuple, std::size_t index >
static void
reserve( uint64_t, Tuple&, std::false_type ){}

template< typename Tuple,
          std::size_t index = ( std::tuple_size< Tuple >::value - 1 )  >
static void
reserve( uint64_t nEntries, Tuple& result, std::true_type = std::true_type() ){
  std::get< index >( result ).resize( nEntries );
  reserve< Tuple, ( index - 1 ) >
    ( nEntries, result, shouldContinueToRecurse< index >() );
}
