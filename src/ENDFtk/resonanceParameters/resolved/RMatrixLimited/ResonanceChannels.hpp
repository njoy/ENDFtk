/**
 *  @class
 *  @brief Resonance channel information for a spin group
 *
 *  The ResonanceChannels class stores the channel data for the current spin
 *  group. It gives the particle pair number, the orbital momentum l, spin s,
 *  boundary condition and the scattering radii for the calculation of the
 *  penetrability, shift factor and phase shift.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ResonanceChannels : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ResonanceChannels/src/generateList.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ResonanceChannels/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ResonanceChannels/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the spin J of the spin group
   */
  auto AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  auto spin() const { return this->AJ(); }

  /**
   *  @brief Return the parity of the spin J
   */
  auto PJ() const { return ListRecord::C2(); }

  /**
  *  @brief Return the parity of the spin J
   */
  auto parity() const { return this->PJ(); }

  /**
   *  @brief Return the background R-matrix option KBK
   */
  auto KBK() const { return ListRecord::L1(); }

  /**
  *  @brief Return the background R-matrix option KBK
   */
  auto backgroundRMatrixOption() const { return this->KBK(); }

  /**
   *  @brief Return the phase shift option
   */
  auto KPS() const { return ListRecord::L2(); }

  /**
  *  @brief Return the phase shift option
   */
  auto phaseShiftOption() const { return this->KPS(); }

  /**
   *  @brief Return the number of channels
   */
  auto NCH() const { return ListRecord::NPL() / 6; }

  /**
  *  @brief Return the number of channels
   */
  long numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto PPI() const {
    return ListRecord::list()
             | ranges::view::stride( 6 )
             | ranges::view::transform( [] ( auto ppi )
                                           { return int( ppi ); } ); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto particlePairNumbers() const { return this->PPI(); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto L() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 1 )
             | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto orbitalMomentumValues() const { return this->L(); }

  /**
   *  @brief Return channel spin values
   */
  auto SCH() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 2 )
             | ranges::view::stride( 6 ); }
 /**
   *  @brief Return channel spin values
   */
  auto channelSpinValues() const { return this->SCH(); }

  /**
   *  @brief Return boundary condition values
   */
  auto BND() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 3 )
             | ranges::view::stride( 6 ); }

  /**
  *  @brief Return boundary condition values
   */
  auto boundaryConditionValues() const { return this->BND(); }

  /**
  *  @brief Return the true channel radii (used in the calculation of the
  *         penetrability and shift factor)
   */
  auto APT() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 5 )
             | ranges::view::stride( 6 ); }

  /**
  *  @brief Return the true channel radii (used in the calculation of the
  *         penetrability and shift factor)
   */
  auto trueChannelRadii() const { return this->APT(); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto APE() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 4 )
             | ranges::view::stride( 6 ); }
  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto effectiveChannelRadii() const { return this->APE(); }

  using ListRecord::NC;
  using ListRecord::print;
};
