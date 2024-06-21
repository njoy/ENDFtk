/**
 *  @brief Return the scattering radius
 *
 *  This function will only return the first true scattering radius value it
 *  finds in the first spin group. If other spin groups use different radii,
 *  AP is meaningless and should not be used as a shortcut to retrieve
 *  the scattering radius.
 */
double AP() const {

  using namespace njoy::tools;
  auto mt = this->particlePairs().MT();
  unsigned int elastic = std20::distance(
                             std20::begin( mt ),
                             std20::find( mt, int( 2 ) ) ) + 1;

  auto channels = this->spinGroups().front().channels();
  auto ppi = channels.particlePairNumbers();
  unsigned int index = std20::distance(
                           std20::begin( ppi ),
                           std20::find( ppi, int( elastic ) ) );
  return channels.trueChannelRadii()[index];
};
