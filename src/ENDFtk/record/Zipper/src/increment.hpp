template< typename Zip, typename Tuple, std::size_t index >
static void
increment( Tuple&, std::false_type ){}

template< typename Zip, typename Tuple,
          std::size_t index = ( std::tuple_size< Tuple >::value - 1 )  >
static void
increment( Tuple& result, std::true_type = std::true_type() ){
  std::get< index >( result ) += Zip::tuplesPerRecord;
  increment< Zip, Tuple, ( index - 1 ) >
    ( result, shouldContinueToRecurse< index >() );
}
