/**
 *  @class
 *  @brief Discrete spectrum information
 *
 *  The DiscreteSpectrum class is used to store spectral information for a
 *  single discrete energy from MF8/MT457.
 *
 *  All quantities are given as values with associated uncertainties so these
 *  are handled as arrays of size 2.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscreteSpectrum : protected ListRecord {

  /* members */

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/verifyNT.hpp"
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/generateList.hpp"
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/returnArray.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of entries
   */
  int NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double RTYP() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto ER() const {

      return std::array< double, 2 >( {{ ListRecord::C1(),
                                         ListRecord::C2() }} );
  }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto discreteEnergy() const { return this->ER(); }

  /**
   *  @brief Return the relative intensity and uncertainty
   */
  auto RI() const { return this->returnArray( 2 ); }

  /**
   *  @brief Return the relative intensity and uncertainty
   */
  auto relativeIntensity() const { return this->RI(); }

  /**
   *  @brief Transition type for beta and electron capture
   */
  double TYPE() const { return ListRecord::list()[1]; }

  /**
   *  @brief Transition type for beta and electron capture
   */
  double type() const { return this->TYPE(); }

  /**
   *  @brief Return the RIS value and its uncertainty, the internal pair
   *         formation coefficient (STYP=0.0) or the positron intensity
   *         (STYP=2.0)
   */
  auto RIS() const { return this->returnArray( 4 ); }

  /**
   *  @brief Return the RIS value and its uncertainty, the internal pair
   *         formation coefficient (STYP=0.0) or the positron intensity
   *         (STYP=2.0)
   */
  auto internalPairFormationCoefficient() const { return this->RIS(); }

  /**
   *  @brief Return the total internal conversion coefficient or RICC value and
   *         its uncertainty (STYP=0.0 only)
   */
  auto RICC() const { return this->returnArray( 6 ); }

  /**
   *  @brief Return the total internal conversion coefficient or RICC value and
   *         its uncertainty (STYP=0.0 only)
   */
  auto totalInternalConversionCoefficient() const { return this->RICC(); }

  /**
   *  @brief Return the K shell internal conversion coefficient or RICK value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto RICK() const { return this->returnArray( 8 ); }

  /**
   *  @brief Return the K shell internal conversion coefficient or RICK value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto internalConversionCoefficientKShell() const { return this->RICK(); }

  /**
   *  @brief Return the L shell internal conversion coefficient or RICL value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto RICL() const { return this->returnArray( 10 ); }

  /**
   *  @brief Return the L shell internal conversion coefficient or RICL value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto internalConversionCoefficientLShell() const { return this->RICL(); }

  using ListRecord::NC;
  using ListRecord::print;
};
