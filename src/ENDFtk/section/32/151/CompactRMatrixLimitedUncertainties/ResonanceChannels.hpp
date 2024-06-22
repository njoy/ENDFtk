/**
 *  @class
 *  @brief Resonance channel information for a spin group
 *
 *  The ResonanceChannels class here is very similar to the MF2 MT151 version
 *  but it does not use KBK and KPS.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT ResonanceChannels : protected ListRecord {

  /* auxiliary functions - blatantly taken from MF2 MT151 LRF = 7 */
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/generateList.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/verifySize.hpp"

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( i )
             | std23::views::stride( 6 );
  }

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceChannels/src/ctor.hpp"

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

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::stride( 6 )
             | std20::views::transform( [] ( auto ppi )
                                                   { return int( ppi ); } ); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto particlePairNumbers() const { return this->PPI(); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto L() const {

    using namespace njoy::tools;
    return ResonanceChannels::column( 1 )
             | std20::views::transform( [] ( auto l )
                                                   { return int( l ); } ); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto orbitalMomentumValues() const { return this->L(); }

  /**
   *  @brief Return the channel spin values
   */
  auto SCH() const { return ResonanceChannels::column( 2 ); }

  /**
   *  @brief Return the channel spin values
   */
  auto channelSpinValues() const { return this->SCH(); }

  /**
   *  @brief Return the boundary condition values
   */
  auto BND() const { return ResonanceChannels::column( 3 ); }

  /**
   *  @brief Return the boundary condition values
   */
  auto boundaryConditionValues() const { return this->BND(); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  auto APT() const { return ResonanceChannels::column( 5 ); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  auto trueChannelRadii() const { return this->APT(); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto APE() const { return ResonanceChannels::column( 4 ); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto effectiveChannelRadii() const { return this->APE(); }

  using ListRecord::NC;
  using ListRecord::print;
};
