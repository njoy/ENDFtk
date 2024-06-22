/**
 *  @class
 *  @brief The l-dependent uncertainties on the scattering radius for the
 *         Reich-Moore formalism
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReichMooreScatteringRadiusUncertainties :
  protected ListRecord {

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
  auto DAPL() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 );
  }

  /**
   *  @brief Return the l-dependent uncertainties
   */
  auto uncertainties() const { return this->DAPL(); }


  using ListRecord::NC;
  using ListRecord::print;
};
