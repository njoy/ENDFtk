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
class ENDFTK_PYTHON_EXPORT EffectiveTemperature : protected TabulationRecord {

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
  auto TMOD() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the moderator temperatures
   */
  auto moderatorTemperatures() const { return this->TMOD(); }

  /**
   *  @brief Return the effective temperatures
   */
  auto TEFF() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the effective temperatures
   */
  auto effectiveTemperatures() const { return this->TEFF(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
