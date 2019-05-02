/**
 *  @class
 *  @brief The Maxwellian fission spectrum (LF=7)
 *
 *  See ENDF102, section 5 for more information.
 */
class MaxwellianFissionSpectrum : protected EffectiveTemperature {

public:

  /* constructor */
  #include "ENDFtk/section/5/MaxwellianFissionSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 7; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int distributionType() {

    return MaxwellianFissionSpectrum::LF();
  }

  using EffectiveTemperature::energies;
  using EffectiveTemperature::thetas;
  using EffectiveTemperature::NP;
  using EffectiveTemperature::NR;
  using EffectiveTemperature::interpolants;
  using EffectiveTemperature::boundaries;
  using EffectiveTemperature::NC;
  using EffectiveTemperature::print;
};