/**
 *  @class
 *  @brief Spectrum information for a specific decay particle type
 *
 *  The DecaySpectrum class is used to store the decay spectrum for a single
 *  particle type from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecaySpectrum {

public:

  using OptionalContinuousSpectrum = std::optional< ContinuousSpectrum >;

private:

  ListRecord data_;
  std::vector< DiscreteSpectrum > discrete_;
  OptionalContinuousSpectrum continuous_;

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/DecaySpectrum/src/verifyLCOV.hpp"
  #include "ENDFtk/section/8/457/DecaySpectrum/src/verifyDiscreteSize.hpp"
  #include "ENDFtk/section/8/457/DecaySpectrum/src/readContinuous.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DecaySpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the radiation type STYP for which spectral data is given
   *         See ENDF102, section 8.4c for more information.
   */
  double STYP() const { return this->data_.C2(); }

  /**
   *  @brief Return the radiation type STYP for which spectral data is given
   *         See ENDF102, section 8.4c for more information.
   */
  double radiationType() const { return this->STYP(); }

  /**
   *  @brief Return the spectral type flag
   */
  int LCON() const { return this->data_.L1(); }

  /**
   *  @brief Return the spectral type flag
   */
  int spectralTypeFlag() const { return this->LCON(); }

  /**
   *  @brief Return the covariance data flag
   */
  int LCOV() const { return this->data_.L2(); }

  /**
   *  @brief Return the covariance data flag
   */
  int covarianceFlag() const { return this->LCOV(); }

  /**
   *  @brief Return the number of discrete decay spectra
   */
  int NER() const { return this->data_.N2(); }

  /**
   *  @brief Return the number of discrete decay spectra
   */
  int numberDiscreteSpectra() const { return this->NER(); }

  /**
   *  @brief Return the discrete normalisation factor and its uncertainty
   */
  auto FD() const {

    return std::array< double, 2 >( {{ this->data_.list()[0],
                                       this->data_.list()[1] }} );
  }

  /**
   *  @brief Return the discrete normalisation factor and its uncertainty
   */
  auto discreteNormalisationFactor() const { return this->FD(); }

  /**
   *  @brief Return the continuous normalisation factor and its uncertainty
   */
  auto FC() const {

    return std::array< double, 2 >( {{ this->data_.list()[4],
                                       this->data_.list()[5] }} );
  }

  /**
   *  @brief Return the continuous normalisation factor and its uncertainty
   */
  auto continuousNormalisationFactor() const { return this->FC(); }

  /**
   *  @brief Return the average decay energy and its uncertainty
   */
  auto ERAV() const {

    return std::array< double, 2 >( {{ this->data_.list()[2],
                                       this->data_.list()[3] }} );
  }

  /**
   *  @brief Return the average decay energy and its uncertainty
   */
  auto averageDecayEnergy() const { return this->ERAV(); }

  /**
   *  @brief Return the discrete spectra, if any are defined
   */
  auto discreteSpectra() const {

    using namespace njoy::tools;
    return std20::views::all( this->discrete_ );
  }

  /**
   *  @brief Return the continuous spectrum, if it is defined
   */
  const OptionalContinuousSpectrum& continuousSpectrum() const {

    return this->continuous_;
  }

  #include "ENDFtk/section/8/457/DecaySpectrum/src/NC.hpp"
  #include "ENDFtk/section/8/457/DecaySpectrum/src/print.hpp"
};
