/**
 *  @class
 *  @brief The general evaporation spectrum (LF=5)
 *
 *  See ENDF102, section 5.1.1.2 for more information.
 */
class GeneralEvaporationSpectrum {

  EffectiveTemperature temperature_;
  Parameter distribution_;

public:

  /* constructor */
  #include "ENDFtk/section/5/GeneralEvaporationSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the effective temperature
   */
  const auto& effectiveTemperature() const { return this->temperature_; }

  /**
   *  @brief Return the distribution function g(x)
   */
  const auto& distributionFunction() const { return this->distribution_; }

  #include "ENDFtk/section/5/GeneralEvaporationSpectrum/src/NC.hpp"
  #include "ENDFtk/section/5/GeneralEvaporationSpectrum/src/print.hpp"
};
