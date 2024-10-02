/**
 *  @brief Return the target spin
 */
double SPI() const {

  using namespace njoy::tools;
  auto mt = this->particlePairs().MT();
  unsigned int index = std20::distance(
                           std20::begin( mt ),
                           std20::find( mt, int( 2 ) ) );
  return this->particlePairs().spinParticleB()[index];
};
