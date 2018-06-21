/**
 *  @class
 *  @brief Tabulated incoherent inelastic scattering law
 *
 *  The Tabulated class is used to represent the case in which the incoherent
 *  inelastic thermal scattering law of the principal scatterer in
 *  ENDF section MF4/MT4 is represented entirely as a tabulated function.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class Tabulated {

public:

  #include "ENDFtk/section/7/4/Tabulated/BetaValue.hpp"

private:

  /* members */
  InterpolationSequenceRecord< BetaValue > data_;

  /* auxiliary functions */

public:
  /* constructor */
  #include "ENDFtk/section/7/4/Tabulated/src/ctor.hpp"

  /* get methods */
  long NR() const { return this->data_.tab2().NR(); }
  long NB() const { return this->data_.tab2().NZ(); }

  auto betas() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/7/4/Tabulated/src/print.hpp"
};
