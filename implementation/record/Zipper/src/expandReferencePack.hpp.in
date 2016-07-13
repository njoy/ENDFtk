template< typename Zip, std::size_t index,
          typename Pack, typename IteratorTuple,
          std::size_t... iteratorIndices, typename... References >
static void
expandReferencePack
( Pack& pack, IteratorTuple&, std::false_type,
  std::index_sequence< iteratorIndices... >, References&... references ){
  process< Zip >( pack, references... );
}

template< typename Zip, std::size_t index = 0,
          typename Pack, typename IteratorTuple,
          std::size_t... iteratorIndices, typename... References >
static void
expandReferencePack
( Pack& pack, IteratorTuple& iteratorTuple, std::true_type,
  std::index_sequence< iteratorIndices... >, References&... references ){
  expandReferencePack< Zip, index + 1 >
    ( pack, iteratorTuple,
      shouldContinueToRecurse< Zip::tuplesPerRecord - index - 1 >(),
      Zip::tupleIndices, references... ,
      std::get< iteratorIndices >( iteratorTuple )[index]... );
}
