/**
 *  @brief Return the target spin
 */
double SPI() const {

  auto mt = this->particlePairs().MT();
  unsigned int index = ranges::distance( ranges::begin( mt ),
                                         ranges::find( mt, int( 2 ) ) );
  return this->particlePairs().spinParticleB()[index];
};
