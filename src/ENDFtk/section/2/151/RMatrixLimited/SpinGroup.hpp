/**
 *  @class
 *  @brief R-matrix limited spin group with resonance parameters
 *
 *  The SpinGroup class is used to represent a spin group in the R-matrix
 *  limited resonance parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class SpinGroup  {

  /* fields */
  ResonanceChannels channels_;
  ResonanceParameters parameters_;
  BackgroundChannels background_;

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/SpinGroup/src/verify.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/SpinGroup/src/ctor.hpp"

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
   *  @brief Return the number of channels with background R-matrix values
   */
  auto KBK() const { return this->channels_.KBK(); }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto numberBackgroundChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of resonances
   */
  auto NRS() const { return this->parameters_.NRS(); }

  /**
   *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRS(); }

  /**
   *  @brief Return the channel information
   */
  const ResonanceChannels& channels() const { return this->channels_; }

  /**
   *  @brief Return the resonance parameters for this spin group
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  /**
   *  @brief Return the background R-matrix values for the spin group channels
   */
  const BackgroundChannels& background() const { return this->background_; }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return this->channels_.NC() + this->parameters_.NC() +
                           this->background_.NC(); };

  #include "ENDFtk/section/2/151/RMatrixLimited/SpinGroup/src/print.hpp"
};
