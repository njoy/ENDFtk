static std::vector< double >
generateList( std::vector< DecayMode >&& modes ) {

  return modes
           | ranges::view::transform(
               [] ( const auto& mode ) -> std::array< double, 6 >
                  { auto q = mode.qValue();
                    auto br = mode.branchingRatio();
                    return {{ mode.decayChain(),
                              mode.finalIsomericState(),
                              q[0], q[1],
                              br[0], br[1] }}; } )
           | ranges::action::join;
}
