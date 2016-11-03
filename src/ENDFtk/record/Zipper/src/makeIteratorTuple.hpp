template< typename... Vectors, std::size_t... indices >
static std::tuple< typename Vectors::iterator... >
makeIteratorTuple
( std::tuple< Vectors... >& vectorTuple, std::index_sequence< indices... > ){
  return std::make_tuple( std::get< indices >( vectorTuple ).begin()... );
}

// explicitly recursive version //
// ---------------------------- //
// template< typename... T, int index, int... indices >
// static std::tuple< typename T::iterator... >
// makeIteratorTuple( std::tuple< T... >& result, std::false_type ){
//   return std::make_tuple( std::get< indices >( result ).begin()... );
// }

// template< typename... T, int index = ( sizeof...( T ) - 1 ), int... indices >
// static std::tuple< typename T::iterator... >
// makeIteratorTuple( std::tuple< T... >& result, std::true_type ){
//   return makeIteratorTuple< T..., index - 1, index, indices... >
//     ( result, shouldContinueToRecurse< index >() );
// }
