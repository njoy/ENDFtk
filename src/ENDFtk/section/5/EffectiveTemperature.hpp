/**
 *  @class
 *  @brief The effective temperature of an evaporation spectrum
 *
 *  The effective temperature is used to describe the secondary
 *  energy distribution for evaporation spectra (LF=5,7,9).
 *
 *  See ENDF102, section 5 for more information.
 */
class EffectiveTemperature : protected Parameter {

public:

  /* constructor */
  using Parameter::Parameter;

  /* get methods */

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return Parameter::x(); }

  /**
   *  @brief Return the effective temperature values
   */
  auto thetas() const { return Parameter::y(); }

  using Parameter::NP;
  using Parameter::NR;
  using Parameter::interpolants;
  using Parameter::boundaries;
  using Parameter::NC;
  using Parameter::print;
};
