/**
 *  @class
 *  @brief The l-dependent uncertainties on the scattering radius for the
 *         Reich-Moore formalism
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ReichMooreScatteringRadiusUncertainties : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ReichMooreScatteringRadiusUncertainties/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/ReichMooreScatteringRadiusUncertainties/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the default scattering radius uncertainty
   */
  double DAP() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the default scattering radius uncertainty
   */
  double defaultUncertainty() const { return this->DAP(); }

  /**
   *  @brief Return the l-dependent uncertainties
   */
  auto uncertainties() const { return ListRecord::list()
                                      | ranges::views::drop_exactly( 1 ); }


  using ListRecord::NC;
  using ListRecord::print;
};
