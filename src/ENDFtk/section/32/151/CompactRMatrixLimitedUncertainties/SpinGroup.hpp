/**
 *  @class
 *  @brief R-matrix limited spin group with resonance parameter uncertainties
 *
 *  The ResonanceChannels class here is very similar to the MF2 MT151 version
 *  but it does not have the background matrix elements.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT SpinGroup  {

  /* fields */
  ResonanceChannels channels_;
  ResonanceParameters parameters_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/SpinGroup/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the spin for this spin group
   */
  double AJ() const { return this->channels_.AJ(); }

  /**
   *  @brief Return the spin for this spin group
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the parity for this spin group
   */
  double PJ() const { return this->channels_.PJ(); }

  /**
   *  @brief Return the parity for this spin group
   */
  double parity() const { return this->PJ(); }

  /**
   *  @brief Return the number of channels
   */
  auto NCH() const { return this->channels_.NCH(); }

  /**
   *  @brief Return the number of channels
   */
  auto numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of resonances
   */
  auto NRSA() const { return this->parameters_.NRSA(); }

  /**
   *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRSA(); }

  /**
   *  @brief Return the channel information
   */
  const ResonanceChannels& channels() const { return this->channels_; }

  /**
   *  @brief Return the resonance parameters for this spin group
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return this->channels_.NC() + this->parameters_.NC(); };

  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/SpinGroup/src/print.hpp"
};
