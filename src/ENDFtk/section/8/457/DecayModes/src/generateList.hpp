static std::vector< double >
generateList( std::vector< DecayMode >&& modes ) {

  return ranges::to< std::vector< double > >(
             modes | ranges::cpp20::views::transform(
                       [] ( const auto& mode ) -> std::array< double, 6 >
                          { auto q = mode.qValue();
                            auto br = mode.branchingRatio();
                            return {{ mode.decayChain(),
                                      mode.finalIsomericState(),
                                      q[0], q[1],
                                      br[0], br[1] }}; } )
                   | ranges::actions::join );
}
