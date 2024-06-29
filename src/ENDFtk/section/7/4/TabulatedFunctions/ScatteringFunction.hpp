/**
 *  @class
 *  @brief S(alpha,beta,T) data for a fixed value of beta
 *
 *  The ScatteringFunction class is used to represent the temperature dependent
 *  S(alpha,beta,T) data for a fixed value of beta from ENDF section MF7/MT4.
 *  It contains a grid of alpha values with a corresponding S(T) grid for each
 *  temperature as well as interpolation information as a function of alpha
 *  and temperature.
 *
 *  Note: temperature interpolation of S(alpha,beta) is discouraged.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class ScatteringFunction {

  /* members */
  TabulationRecord alphas_;
  std::vector< ListRecord > temperatures_;

  using Array = decltype( alphas_.y() );
  std::vector< Array > s_;

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/generateS.hpp"
  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/generateTemperatures.hpp"
  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/verifyBetaValues.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the current beta value
   */
  double B() const { return this->alphas_.C2(); }

  /**
   *  @brief Return the current beta value
   */
  double beta() const { return this->B(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int LT() const { return this->alphas_.L1(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int temperatureDependenceFlag() const { return this->LT(); }

  /**
   *  @brief Return the number of temperatures NT for which thermal scattering
   *         law data is given
   */
  int NT() const { return this->temperatures_.size() + 1; }

  /**
   *  @brief Return the number of temperatures NT for which thermal scattering
   *         law data is given
   */
  int numberTemperatures() const { return this->NT(); }

  /**
   *  @brief Return the number of interpolation ranges on the alpha grid
   */
  long NR() const { return this->alphas_.NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the alpha grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of alpha values
   */
  long NP() const { return this->alphas_.NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long numberPoints() const { return this->NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long NA() const { return this->alphas_.NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long numberAlphas() const { return this->NA(); }

  /**
   *  @brief Return interpolation type for each range on the alpha grid
   */
  auto INT() const { return this->alphas_.INT(); }

  /**
   *  @brief Return interpolation type for each range on the alpha grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the alpha grid
   */
  auto NBT() const { return this->alphas_.NBT(); }

  /**
   *  @brief Return interpolation boundaries for the alpha grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto T() const {

    using namespace njoy::tools;
    std::vector< double > temperatures = { this->alphas_.C1() };
    auto data = this->temperatures_ | std20::views::transform( [] ( const auto& v )
                                                                  { return v.C1(); } );
    temperatures.insert( temperatures.end(), data.begin(), data.end() );
    return temperatures;
  }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto temperatures() const { return this->T(); }

  /**
   *  @brief Return the alpha grid
   */
  auto A() const { return this->alphas_.x(); }

  /**
   *  @brief Return the alpha grid
   */
  auto alphas() const { return this->A(); }

  /**
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto LI() const {

    using namespace njoy::tools;
    return this->temperatures_ | std20::views::transform( [] ( const auto& v )
                                                             { return v.L1(); } );
  }

  /**
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto temperatureInterpolants() const { return this->LI(); }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto S() const {

    using namespace njoy::tools;
    return this->s_ | std20::views::all;
 }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto thermalScatteringValues() const { return this->S(); }

  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/NC.hpp"
  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction/src/print.hpp"
};
