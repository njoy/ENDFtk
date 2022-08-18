static std::vector< double >
generateList( std::vector< DecayMode >&& modes ) {

  std::vector< double > list;
  for ( const auto& mode : modes ) {

    auto q = mode.qValue();
    auto br = mode.branchingRatio();
    list.push_back( mode.decayChain() );
    list.push_back( mode.finalIsomericState() );
    list.insert( list.end(), q.begin(), q.end() );
    list.insert( list.end(), br.begin(), br.end() );
  }
  return list;
}
