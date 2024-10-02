/**
 *  @class
 *  @brief Tabulated incoherent inelastic scattering law
 *
 *  The Tabulated class is used to represent the case in which the incoherent
 *  inelastic thermal scattering law of the principal scatterer in
 *  ENDF section MF4/MT4 is represented entirely as a tabulated function.
 *
 *  The tabulated S(alpha,beta,T) functions are given as tabulated S(alpha,T)
 *  functions for fixed beta values.
 *
 *  See ENDF102, section 7.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedFunctions {

public:

  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction.hpp"

private:

  /* members */
  InterpolationSequenceRecord< ScatteringFunction > data_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/7/4/TabulatedFunctions/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of interpolation ranges on the beta grid
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the beta grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of beta values
   */
  long NB() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of beta values
   */
  long numberBetas() const { return this->NB(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto B() const {

    using namespace njoy::tools;
    return this->data_.records() | std20::views::transform( [] ( const auto& record )
                                                               { return record.beta(); } );
  }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto betas() const { return this->B(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto S() const { return this->data_.records(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto scatteringFunctions() const {

    return this->S();
  }

  /**
   *  @brief Return the interpolation type for each range on the beta grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return the interpolation type for each range on the beta grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation boundaries for the beta grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return the interpolation boundaries for the beta grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the number of lines in this MF7/MT4 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/7/4/TabulatedFunctions/src/print.hpp"
};
