static std::vector< double >
generateList( std::vector< DecayMode >&& modes ) {

  std::vector< double > list;
  for ( const auto& current : modes ) {

    list.push_back( current.decayChain() );
    list.push_back( current.finalIsomericState() );

    const auto& q = current.qValue();
    list.push_back( std::get< 0 >( q ) );
    list.push_back( std::get< 1 >( q ) );

    const auto& branch = current.branchingRatio();
    list.push_back( std::get< 0 >( branch ) );
    list.push_back( std::get< 1 >( branch ) );
  }
  return list;
}
