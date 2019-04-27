/**
 *  @class
 *  @brief The evaporation spectrum (LF=9)
 *
 *  See ENDF102, section 5 for more information.
 */
class EvaporationSpectrum : protected EffectiveTemperature {

public:

  /* constructor */
  #include "ENDFtk/section/5/EvaporationSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 9; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int distributionType() {

    return EvaporationSpectrum::LF();
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
