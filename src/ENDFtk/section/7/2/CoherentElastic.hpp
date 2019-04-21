/**
 *  @class
 *  @brief Coherent elastic scattering law
 *
 *  The CoherentElastic class is used to represent the coherent elastic
 *  scattering law of MF7/MT2.
 *
 *  The S(E) functions are given as tabulated S(E) for a set of temperature
 *  values.
 *
 *  See ENDF102, section 7.2 for more information.
 */
class CoherentElastic {

  /* members */
  TabulationRecord principal_;
  std::vector< ListRecord > temperatures_;

  /* auxiliary functions */
  #include "ENDFtk/section/7/2/CoherentElastic/src/generateTemperatures.hpp"
  #include "ENDFtk/section/7/2/CoherentElastic/src/readTemperatures.hpp"
  #include "ENDFtk/section/7/2/CoherentElastic/src/verifyTemperatures.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/7/2/CoherentElastic/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LTHR flag for coherent elastic scattering
   */
  static constexpr int LTHR() { return 1; }

  /**
   *  @brief Return the LTHR flag for coherent elastic scattering
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int LT() const { return this->principal_.L1(); }

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
   *  @brief Return the number of interpolation ranges on the energy grid
   */
  long NR() const { return this->principal_.NR(); }

  /** 
   *  @brief Return the number of energy values
   */
  long NP() const { return this->principal_.NP(); }

  /** 
   *  @brief Return interpolation type for each range on the energy grid
   */
  auto interpolants() const { return this->principal_.interpolants(); }

  /** 
   *  @brief Return interpolation boundaries for the energy grid
   */
  auto boundaries() const { return this->principal_.boundaries(); }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto temperatures() const {
    return ranges::view::concat(
             ranges::view::single( this->principal_.C1() ), 
             this->temperatures_ | 
                 ranges::view::transform( [] ( const auto& v )
                                             { return v.C1(); } ) );
  }

  /**
   *  @brief Return the energy grid
   */
  auto energies() const { return this->principal_.x(); }

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
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto temperatureInterpolants() const { return this->LI(); }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto thermalScatteringValues() const {
    return ranges::view::concat(
             ranges::view::single( this->principal_.y() ), 
             this->temperatures_ |
                 ranges::view::transform( [] ( const auto& v )
                                             { return v.list(); } ) );
  }

  #include "ENDFtk/section/7/2/CoherentElastic/src/NC.hpp"
  #include "ENDFtk/section/7/2/CoherentElastic/src/print.hpp"
};
