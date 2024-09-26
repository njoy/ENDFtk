/**
 *  @class
 *  @brief Resonance parameters for a spin group
 *
 *  The ResonanceParameters class stores the resonance parameters for the current
 *  spin group. It gives the resonance parameters sorted by energy.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/generateList.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of resonances
   */
  auto NRS() const { return ListRecord::L2(); }

  /**
  *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRS(); }

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
    return ListRecord::list()
             | std23::views::stride( this->NX() / this->NRS() * 6 ); }

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
             | std23::views::chunk( this->NX() / this->NRS() * 6 )
             | std20::views::transform(
                   [] ( auto&& chunk )
                      { return chunk | std20::views::drop( 1 ); } ); }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const { return this->GAM(); }

  using ListRecord::NC;
  using ListRecord::print;
};
