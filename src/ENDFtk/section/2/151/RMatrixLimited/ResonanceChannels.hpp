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

public:

  using Column = StrideRange< DropRange< AllRange< double > > >;

private:

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/generateList.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/verifySize.hpp"

  Column column( unsigned int i ) const {

    return ListRecord::list()
             | ranges::views::drop_exactly( i )
             | ranges::views::stride( 6 );
  }

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the spin J of the spin group
   */
  double AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the parity of the spin J
   */
  double PJ() const { return ListRecord::C2(); }

  /**
  *  @brief Return the parity of the spin J
   */
  double parity() const { return this->PJ(); }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto KBK() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto numberBackgroundChannels() const { return this->KBK(); }

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
  unsigned int NCH() const { return ListRecord::NPL() / 6; }

  /**
  *  @brief Return the number of channels
   */
  unsigned int numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto PPI() const {
    return ListRecord::list()
             | ranges::views::stride( 6 )
             | ranges::cpp20::views::transform( [] ( auto ppi )
                                                   { return int( ppi ); } ); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto particlePairNumbers() const { return this->PPI(); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto L() const {
    return ResonanceChannels::column( 1 )
             | ranges::cpp20::views::transform( [] ( auto l )
                                                   { return int( l ); } ); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto orbitalMomentumValues() const { return this->L(); }

  /**
   *  @brief Return the channel spin values
   */
  Column SCH() const { return ResonanceChannels::column( 2 ); }

  /**
   *  @brief Return the channel spin values
   */
  Column channelSpinValues() const { return this->SCH(); }

  /**
   *  @brief Return the boundary condition values
   */
  Column BND() const { return ResonanceChannels::column( 3 ); }

  /**
   *  @brief Return the boundary condition values
   */
  Column boundaryConditionValues() const { return this->BND(); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  Column APT() const { return ResonanceChannels::column( 5 ); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  Column trueChannelRadii() const { return this->APT(); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  Column APE() const { return ResonanceChannels::column( 4 ); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  Column effectiveChannelRadii() const { return this->APE(); }

  using ListRecord::NC;
  using ListRecord::print;
};
