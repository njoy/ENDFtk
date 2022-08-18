/**
 *  @brief Return the target spin
 */
double SPI() const {

  auto mt = this->particlePairs().MT();
  unsigned int index = std::distance(
                           mt.begin(),
                           std::find( mt.begin(), mt.end(), int( 2 ) ) );
  return this->particlePairs().spinParticleB()[index];
};
