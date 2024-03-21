/**
 *  @class
 *  @brief Resonance parameter uncertainties for a spin group
 *
 *  The ResonanceParameters class here is very similar to the MF2 MT151 version
 *  but it adds resonance energy and resonance parameter uncertainties. The
 *  evaluations do not seem to follow the format as given in the manual either
 *  it seems. What is implemented here is what the evaluations use, not what
 *  the manual says it should be - because why the hell would we follow the
 *  format standard in the first place if we can just wing it.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceParameters/src/generateList.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceParameters/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceParameters/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of resonances
   */
  auto NRSA() const { return ListRecord::L2(); }

  /**
  *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRSA(); }

  /**
   *  @brief Return the number of lines for all parameters
   */
  auto NX() const { return ListRecord::NPL() / 12; }

  /**
  *  @brief Return the number of lines for all parameters
   */
  long numberLines() const { return this->NX(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const {

    return ListRecord::list()
             | ranges::views::stride( this->NX() / this->NRSA() * 12 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const {

    return this->ER();
  }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto DER() const {

    return ListRecord::list()
             | ranges::views::drop_exactly( this->NX() / this->NRSA() * 6 )
             | ranges::views::stride( this->NX() / this->NRSA() * 12 ); }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto resonanceEnergyUncertainties() const {

    return this->DER();
  }

  /**
   *  @brief Return the resonance parameters
   */
  auto GAM() const {
    return ListRecord::list()
             | ranges::views::chunk( this->NX() / this->NRSA() * 6 )
             | ranges::views::stride( 2 )
             | ranges::cpp20::views::transform(
                   [] ( auto chunk )
                      { return chunk | ranges::views::drop_exactly( 1 ); } ); }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const { return this->GAM(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  auto DGAM() const {
    return ListRecord::list()
             | ranges::views::drop_exactly( this->NX() / this->NRSA() * 6 )
             | ranges::views::chunk( this->NX() / this->NRSA() * 6 )
             | ranges::views::stride( 2 )
             | ranges::cpp20::views::transform(
                   [] ( auto chunk )
                      { return chunk | ranges::views::drop_exactly( 1 ); } ); }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameterUncertainties() const { return this->DGAM(); }

  using ListRecord::NC;
  using ListRecord::print;
};
