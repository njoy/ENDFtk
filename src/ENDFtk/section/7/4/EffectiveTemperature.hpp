/**
 *  @class
 *  @brief Effective temperatures for the short collision-time approximation
 *
 *  The EffectiveTemperature class is used to represent the temperature
 *  dependent effective temperature for a scattering atom (both principal or
 *  secondary).
 *
 *  See ENDF102, section 7.4 for more information.
 */
class EffectiveTemperature : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/7/4/EffectiveTemperature/src/ctor.hpp"

  /* get methods */
  long NT() const { return TabulationRecord::NP(); }
  long numberTemperatures() const { return this->NT(); }
  using TabulationRecord::NR;
  auto moderatorTemperatures() const { return TabulationRecord::x(); }
  auto effectiveTemperatures() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};

