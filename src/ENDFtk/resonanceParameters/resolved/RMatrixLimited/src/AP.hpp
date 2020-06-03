/**
 *  @brief Return the target spin
 */
double AP() const {

  auto mt = this->particlePairs().MT();
  unsigned int elastic = ranges::distance( ranges::begin( mt ),
                                           ranges::find( mt, int( 2 ) ) ) + 1;

  auto channels = this->spinGroups().front().channels();
  auto ppi = channels.particlePairNumbers();
  unsigned int index = ranges::distance( ranges::begin( ppi ),
                                         ranges::find( ppi, int( elastic ) ) );
  return channels.trueChannelRadii()[index];
};
