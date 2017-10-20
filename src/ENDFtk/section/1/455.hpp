template<>
class Type< 1, 455 > : protected Base {
protected:

  /* fields */
  int ldg_;
  int lnu_;
  nubar::DecayConstantData lambda_;
  nubar::NubarData nubar_;

public:

  /* constructor */
#include "ENDFtk/section/1/455/src/ctor.hpp"

  /* set methods */

  /* get methods */
  static constexpr int MT() { return 455; }

  int LNU() const { return this->lnu_; }
//! @todo use this as an alternative and do not store LNU in the section?
// NOTE: LNU is on the HEAD record of the section, not on the LIST or TAB1
//  int LNU() const { return std::visit( [] ( const auto& v ) -> long
//                                          { return v.LNU(); },
//                                       this->nubar_ ); }

  int LDG() const { return this->ldg_; }
//! @todo use this as an alternative and do not store LDG in the section?
// NOTE: LDG is on the HEAD record of the section, not on the LIST or TAB2+LISTs
//  int LDG() const { return std::visit( [] ( const auto& v ) -> long
//                                          { return v.LDG(); },
//                                       this->lambda_ ); }

  const nubar::DecayConstantData& lambda() const { return this->lambda_; }

  const nubar::NubarData& nubar() const { return this->nubar_; }

  long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->lambda_ )
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->nubar_ ); }

#include "ENDFtk/section/1/455/src/print.hpp"

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

