static std::vector< double >
generateList( std::vector< DecayMode >&& modes ) {

  std::vector< double > list;
  list.reserve( modes.size() * 6 );

  using namespace njoy::tools;
  auto data = modes | std20::views::transform(
                       [] ( const auto& mode ) -> std::vector< double >
                          { auto q = mode.qValue();
                            auto br = mode.branchingRatio();
                            return {{ mode.decayChain(),
                                      mode.finalIsomericState(),
                                      q[0], q[1],
                                      br[0], br[1] }}; } );
  for (auto&& entry : data ) {

    list.insert( list.end(), entry.begin(), entry.end() );
  }
  return list;
}
