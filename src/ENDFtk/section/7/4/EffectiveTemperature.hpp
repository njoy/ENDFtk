/**
 *  @class
 *  @brief Effective temperatures for the short collision-time approximation
 *
 *  The EffectiveTemperature class is used to represent the temperature
 *  dependent effective temperature for a scattering atom (both principal or
 *  secondary).
 *
 *  See ENDF102, section 7.5 for more information.
 */
class EffectiveTemperature : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/7/4/EffectiveTemperature/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of temperature values
   */
  long NT() const { return TabulationRecord::NP(); }

  /**
   *  @brief Return the number of temperature values
   */
  long numberTemperatures() const { return this->NT(); }

  /**
   *  @brief Return the moderator temperatures
   */
  AllRange< double > TMOD() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the moderator temperatures
   */
  AllRange< double > moderatorTemperatures() const { return this->TMOD(); }

  /**
   *  @brief Return the effective temperatures
   */
  AllRange< double > TEFF() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the effective temperatures
   */
  AllRange< double > effectiveTemperatures() const { return this->TEFF(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
