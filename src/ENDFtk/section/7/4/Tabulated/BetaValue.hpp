/**
 *  @class
 *  @brief S(alpha,beta,T) data for a fixed value of beta
 *
 *  The BetaValue class is used to represent the temperature dependent
 *  S(alpha,beta,T) data for a fixed value of beta from ENDF section MF7/MT4.
 *  It contains a grid of alpha values with a corresponding S(T) grid for each
 *  temperature.
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

public:

  /* constructor */
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/ctor.hpp"

  /* get methods */
  double beta() const { return this->alphas_.C2(); }
  double LT() const { return this->alphas_.L1(); }

  long NR() const { return this->alphas_.NR(); }
  long NP() const { return this->alphas_.NP(); }

  auto interpolants() const { return this->alphas_.interpolants(); }
  auto boundaries() const { return this->alphas_.boundaries(); }

  auto temperatures() const {
    return ranges::view::concat(
             ranges::view::single( this->alphas_.C1() ), 
             ranges::view::transform( this->temperatures_,
                                      [] ( const auto& v )
                                         { return v.C1(); } ) );
  }

  auto alphas() const { return this->alphas_.x(); }

  auto LI() const {
    return ranges::view::transform( this->temperatures_,
                                    [] ( const auto& v ) { return v.L1(); } );
  }

  auto thermalScatteringValues() const {
    return ranges::view::concat(
             ranges::view::single( this->alphas_.y() ), 
             ranges::view::transform( this->temperatures_,
                                      [] ( const auto& v )
                                         { return v.list(); } ) );
  }

  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/NC.hpp"
  #include "ENDFtk/section/7/4/Tabulated/BetaValue/src/print.hpp"
};
