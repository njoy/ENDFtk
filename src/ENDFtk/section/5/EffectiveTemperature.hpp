/**
 *  @class
 *  @brief The effective temperature of an evaporation spectrum
 *
 *  The effective temperature is used to describe the secondary
 *  energy distribution for evaporation spectra (LF=5,7,9).
 *
 *  See ENDF102, section 5 for more information.
 */
class EffectiveTemperature : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/EffectiveTemperature/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the effective temperature values
   */
  auto thetas() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
