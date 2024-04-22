/**
 *  @class
 *  @brief The evaporation spectrum (LF=9)
 *
 *  See ENDF102, section 5.1.1.4 and 5.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT EvaporationSpectrum : protected EffectiveTemperature {

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
  int LAW() const { return this->LF(); }

  using EffectiveTemperature::E;
  using EffectiveTemperature::energies;
  using EffectiveTemperature::thetas;
  using EffectiveTemperature::NP;
  using EffectiveTemperature::numberPoints;
  using EffectiveTemperature::NR;
  using EffectiveTemperature::numberInterpolationRegions;
  using EffectiveTemperature::INT;
  using EffectiveTemperature::interpolants;
  using EffectiveTemperature::NBT;
  using EffectiveTemperature::boundaries;
  using EffectiveTemperature::NC;
  using EffectiveTemperature::print;
};
