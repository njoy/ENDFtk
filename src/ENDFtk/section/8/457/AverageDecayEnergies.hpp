/**
 *  @class
 *  @brief Half life information and average decay energies for radiation types
 *
 *  The AverageDecayEnergies class is used to store the half life and the 
 *  average decay energies from MF8/MT457.
 *
 *  All quantities are given as values with associated uncertainties so these
 *  are handled as tuples.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class AverageDecayEnergies : protected ListRecord {

  /* members */

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/AverageDecayEnergies/src/verifyNC.hpp"
  #include "ENDFtk/section/8/457/AverageDecayEnergies/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/8/457/AverageDecayEnergies/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto halfLife() const {
      return std::tuple< double, double >( ListRecord::C1(),
                                           ListRecord::C2() ); }

  /**
   *  @brief Return the number of decay energy values NC
   */
  int numberDecayEnergies() const { return ListRecord::NPL() / 2; }

  /**
   *  @brief Return the decay energies and their uncertainties
   *
   *  This returns a range of pairs (the decay energy value and its uncertainty)
   */
  auto decayEnergies() const { 

    return
        ranges::view::zip(
            ListRecord::list() | ranges::view::stride( 2 ),
            ListRecord::list() | ranges::view::drop_exactly( 1 )
                               | ranges::view::stride( 2 ) );
  }

  /**
   *  @brief Return the decay energy and uncertainty for light particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  light particles.
   */
  auto lightParticleDecayEnergy() const { return this->decayEnergies()[0]; }

  /**
   *  @brief Return the decay energy and uncertainty for electromagnetic
   *         radiation.
   *
   *  This is always present.
   */
  auto electromagneticDecayEnergy() const { return this->decayEnergies()[1]; }

  /**
   *  @brief Return the decay energy and uncertainty for heavy particle decay
   *
   *  This is always present and equal to the sum of decay energies for all
   *  heavy particles (neutrons, alphas, spontaneous fission, etc.).
   */
  auto heavyParticleDecayEnergy() const { return this->decayEnergies()[2]; }

  using ListRecord::NC;
  using ListRecord::print;
};
