/**
 *  @class
 *  @brief The Watt fission spectrum (LF=11)
 *
 *  See ENDF102, section 5.1.1.5 and 5.2.5 for more information.
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
  static constexpr int LAW() { return WattSpectrum::LF(); }

  /**
   *  @brief Return the a parameter data
   */
  const auto& a() const { return this->parameters_[0]; }

  /**
   *  @brief Return the b parameter data
   */
  const auto& b() const { return this->parameters_[1]; }

  #include "ENDFtk/section/5/WattSpectrum/src/NC.hpp"
  #include "ENDFtk/section/5/WattSpectrum/src/print.hpp"
};

