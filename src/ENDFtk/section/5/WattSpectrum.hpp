/**
 *  @class
 *  @brief The Watt fission spectrum (LF=11)
 *
 *  See ENDF102, section 5.1.1.5 for more information.
 */
class WattSpectrum {

  std::array< Parameter, 2 > parameters_;

  /* auxiliary functions */
  #include "ENDFtk/section/5/WattSpectrum/src/readParameters.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/5/WattSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 11; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int distributionType() { return WattSpectrum::LF(); }

  /**
   *  @brief Return the parameters
   */
  auto parameters() const { return ranges::view::all( this->parameters_ ); }

  /**
   *  @brief Return the a parameter data
   */
  const auto& aParameter() const { return this->parameters_[0]; }

  /**
   *  @brief Return the b parameter data
   */
  const auto& bParameter() const { return this->parameters_[1]; }

  #include "ENDFtk/section/5/WattSpectrum/src/NC.hpp"
  #include "ENDFtk/section/5/WattSpectrum/src/print.hpp"
};
