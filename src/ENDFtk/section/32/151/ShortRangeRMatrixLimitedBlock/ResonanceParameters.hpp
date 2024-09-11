/**
 *  @class
 *  @brief Resonance parameters for a spin group
 *
 *  The ResonanceParameters class stores the resonance parameters for which
 *  covariance information will be given. It is very similar to the MF2 MT151
 *  format.
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/ResonanceParameters/src/generateList.hpp"
  // blatantly copied from MF2 MT151
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/ResonanceParameters/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of channels
   */
  auto NCH() const { return ListRecord::L1(); }

  /**
  *  @brief Return the number of channels
   */
  auto numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of resonances
   */
  auto NRB() const { return ListRecord::L2(); }

  /**
  *  @brief Return the phase shift option
   */
  auto numberResonances() const { return this->NRB(); }

  /**
   *  @brief Return the number of lines for all parameters
   */
  auto NX() const { return ListRecord::NPL() / 6; }

  /**
  *  @brief Return the number of lines for all parameters
   */
  long numberLines() const { return this->NX(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( this->NX() / this->NRB() * 6 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const {

    return this->ER();
  }

  /**
   *  @brief Return the resonance parameters
   */
  auto GAM() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::chunk( this->NX() / this->NRB() * 6 )
             | std20::views::transform(
                   [] ( auto chunk )
                      { return chunk | std20::views::drop( 1 ); } );
  }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const { return this->GAM(); }

  using ListRecord::NC;
  using ListRecord::print;
};
