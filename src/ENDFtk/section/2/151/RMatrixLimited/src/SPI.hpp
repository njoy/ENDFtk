/**
 *  @brief Return the target spin
 */
double SPI() const {

  auto mt = this->particlePairs().MT();
  unsigned int index = ranges::cpp20::distance(
                           ranges::cpp20::begin( mt ),
                           ranges::cpp20::find( mt, int( 2 ) ) );
  return this->particlePairs().spinParticleB()[index];
};
