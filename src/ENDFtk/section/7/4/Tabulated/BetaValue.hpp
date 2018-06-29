/**
 *  @class
 *  @brief S(alpha,beta,T) data for a fixed value of beta
 *
 *  The BetaValue class is used to represent the temperature dependent
 *  S(alpha,beta,T) data for a fixed value of beta from ENDF section MF7/MT4.
 *  It contains a grid of alpha values with a corresponding S(T) grid for each
 *  temperature as well as interpolation interformation as a function of alpha
 *  and temperature.
 *
 *  Note: temperature interpolation of S(alpha,beta) is discouraged.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class BetaValue {

  /* members */
  TabulationRecord alphas_;
  std::vector< ListRecord > temperatures_;

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/readTemperatures.hpp"
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/generateTemperatures.hpp"
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/verifyLT.hpp"
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/verifyBetaValues.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the current beta value
   */
  double beta() const { return this->alphas_.C2(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int LT() const { return this->alphas_.L1(); }

  /**
   *  @brief Return the number of temperatures NT for which thermal scattering
   *         law data is given
   */
  int NT() const { return this->temperatures_.size() + 1; }

  /** 
   *  @brief Return the number of interpolation ranges on the alpha grid
   */
  long NR() const { return this->alphas_.NR(); }

  /** 
   *  @brief Return the number of alpha values
   */
  long NA() const { return this->alphas_.NP(); }

  /** 
   *  @brief Return interpolation type for each range on the alpha grid
   */
  auto interpolants() const { return this->alphas_.interpolants(); }

  /** 
   *  @brief Return interpolation boundaries for the alpha grid
   */
  auto boundaries() const { return this->alphas_.boundaries(); }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto temperatures() const {
    return ranges::view::concat(
             ranges::view::single( this->alphas_.C1() ), 
             this->temperatures_ | 
                 ranges::view::transform( [] ( const auto& v )
                                             { return v.C1(); } ) );
  }

  /**
   *  @brief Return the alpha grid
   */
  auto alphas() const { return this->alphas_.x(); }

  /**
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto LI() const {
    return this->temperatures_ |
               ranges::view::transform( [] ( const auto& v )
                                           { return v.L1(); } );
  }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto thermalScatteringValues() const {
    return ranges::view::concat(
             ranges::view::single( this->alphas_.y() ), 
             this->temperatures_ |
                 ranges::view::transform( [] ( const auto& v )
                                             { return v.list(); } ) );
  }

  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/NC.hpp"
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/print.hpp"
};
